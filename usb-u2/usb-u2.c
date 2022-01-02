/*
 * usb-u2: A bare minimum USB stack for atmega{8,16,32}u2.
 *
 * SPDX-FileCopyrightText: 2021-2022 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>
#include <stdlib.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "usb-u2.h"

static volatile uint8_t config;
static volatile uint8_t num_configs;
static volatile uint8_t epmax;
static volatile uint8_t ep0size;
static volatile uint8_t state = USB_U2_STATE_DEFAULT;
static usb_u2_control_request_t req;

static const usb_u2_string_descriptor_t default_enus_lang PROGMEM = {
    .bLength = 4,
    .bDescriptorType = USB_U2_DESCR_TYPE_STRING,
    .wData = {0x0409},
};


void
usb_u2_init(void)
{
    if (state != USB_U2_STATE_DEFAULT)
        return;

    // make sure that 3.3v regulator is on
    REGCR = 0;

    // disable interrupts
    UDIEN = 0;
    UDINT = 0;

    // enable controller
    USBCON = (1 << USBE) | (1 << FRZCLK);
    USBCON = (1 << USBE);

    // enable PLL prescaler, and enable PLL afterwards
#if F_CPU == 8000000UL
    PLLCSR = 0;
#elif F_CPU == 16000000UL
    PLLCSR = (1 << PLLP0);
#else
    #error "Unsupported CPU frequency"
#endif
    PLLCSR |= (1 << PLLE);
    while (!(PLLCSR & (1 << PLOCK)));

    // enable interrupt
    // FIXME: handle suspend
    UDIEN = (1 << EORSTE);

    // attach usb
    UDCON &= ~(1 << DETACH);
}


ISR(USB_GEN_vect)
{
    if ((UDINT & (1 << EORSTI)) == 0)
        return;

    // ack interrupt
    UDINT &= ~(1 << EORSTI);

    // configure endpoint 0
    const usb_u2_device_descriptor_t *desc = usb_u2_device_descriptor_cb();
    if (desc == NULL)
        return;

    ep0size = pgm_read_word_near(&(desc->bMaxPacketSize0));
    num_configs = pgm_read_word_near(&(desc->bNumConfigurations));

    UENUM = 0;
    UECONX |= (1 << EPEN);
    UECFG0X = 0;
    UECFG1X = ((ep0size <= 8) ? 0 : ((ep0size <= 16) ? 1 :
        ((ep0size <= 32) ? 2 : 3)) << EPSIZE0) | (1 << ALLOC);

    state = USB_U2_STATE_DEFAULT;

    config = 0;
    epmax = 0;

    if (usb_u2_reset_hook_cb != NULL)
        usb_u2_reset_hook_cb();
}


uint8_t
usb_u2_control_in(const uint8_t *b, size_t len, bool from_progmem)
{
    UENUM = 0;

    if ((UEINTX & (1 << RXSTPI)) == 0)
        return 0;
    UEINTX &= ~(1 << RXSTPI);

    // DATA STAGE

    // if host requested more data than we are planning to send, and we are
    // going to send a multiple of the endpoint 0 size, we must close the data
    // transmission with a zero length package.
    bool with_zlp = (req.wLength > len) && (len % ep0size == 0);

    // we can't send more data than requested by host
    if (len > req.wLength)
        len = req.wLength;

    if (len == 0)
        UEINTX &= ~(1 << TXINI);

    uint8_t i = 0;

    while (len > 0) {
        while ((UEINTX & (1 << TXINI)) == 0);

        while (len > 0 && UEBCLX < ep0size) {
            UEDATX = from_progmem ? pgm_read_byte_near(&(b[i++])) : b[i++];
            len--;
        }

        UEINTX &= ~(1 << TXINI);
    }

    if (with_zlp) {
        while ((UEINTX & (1 << TXINI)) == 0);
        UEINTX &= ~(1 << TXINI);
    }

    // STATUS STAGE

    while ((UEINTX & (1 << RXOUTI)) == 0);
    UEINTX &= ~(1 << RXOUTI);

    return i;
}


uint8_t
usb_u2_control_out(uint8_t *b, size_t len)
{
    UENUM = 0;

    if ((UEINTX & (1 << RXSTPI)) == 0)
        return 0;
    UEINTX &= ~(1 << RXSTPI);

    // DATA STAGE

    // we can't read more data than sent by host
    if (len > req.wLength)
        len = req.wLength;

    if (len == 0)
        UEINTX &= ~(1 << RXOUTI);

    uint8_t i = 0;

    while (len > 0) {
        while ((UEINTX & (1 << RXOUTI)) == 0);

        while (len > 0 && UEBCLX > 0) {
            b[i++] = UEDATX;
            len--;
        }

        UEINTX &= ~(1 << RXOUTI);
    }

    while ((UEINTX & (1 << TXINI)) == 0);

    return i;
}


void
usb_u2_control_out_status(void)
{
    UENUM = 0;

    if ((UEINTX & ((1 << RXSTPI) | (1 << RXOUTI))) != 0)
        return;

    UEINTX &= ~(1 << TXINI);
    while ((UEINTX & (1 << TXINI)) == 0);
}


void
usb_u2_endpoint_select(uint8_t ep)
{
    // series 2 don't have more than 5 endpoints (including 0)
    if (ep > 4)
        return;

    UENUM = ep;
}


bool
usb_u2_endpoint_in_ready(void)
{
    return (UEINTX & (1 << TXINI)) != 0;
}


uint8_t
usb_u2_endpoint_in(const uint8_t *b, size_t len)
{
    if (b == NULL || (UEINTX & (1 << TXINI)) == 0)
        return 0;

    uint8_t i = 0;

    while (len > 0 && (UEINTX & (1 << RWAL)) != 0) {
        UEDATX = b[i++];
        len--;
    }

    UEINTX &= ~((1 << TXINI) | (1 << FIFOCON));

    return i;
}


bool
usb_u2_endpoint_out_received(void)
{
    return (UEINTX & (1 << RXOUTI)) != 0;
}


uint8_t
usb_u2_endpoint_out(uint8_t *data, uint8_t len)
{
    if ((UEINTX & (1 << RXOUTI)) == 0)
        return 0;

    uint8_t i = 0;

    while ((UEINTX & (1 << RWAL)) != 0) {
        if (i < len) {
            data[i++] = UEDATX;
        }
        else {
            uint8_t dummy = UEDATX;
            (void) dummy;
        }
    }

    if (i == 0)
        return 0;

    UEINTX &= ~((1 << RXOUTI) | (1 << FIFOCON));
    return i;
}


static void
handle_ctrl(void)
{
    // read request beforehand to make sure we cleanup fifo
    uint8_t *tmp = (uint8_t*) &req;
    for (uint8_t i = 0; i < sizeof(usb_u2_control_request_t); i++)
        tmp[i] = UEDATX;

    switch (req.bmRequestType & USB_U2_REQ_TYPE_MASK) {
        case USB_U2_REQ_TYPE_STANDARD:
            break;

        case USB_U2_REQ_TYPE_VENDOR:
            if (usb_u2_control_vendor_cb != NULL)
                usb_u2_control_vendor_cb(&req);

        default:
            goto _stall;
    }

    switch (req.bRequest) {
        case USB_U2_REQ_GET_STATUS: {
            if ((req.bmRequestType & USB_U2_REQ_DIR_MASK) == USB_U2_REQ_DIR_HOST_TO_DEVICE)
                break;

            uint16_t status = 0;
            if ((req.bmRequestType & USB_U2_REQ_RCPT_MASK) == USB_U2_REQ_RCPT_DEVICE) {
                // FIXME: handle remote wakeup and self powered
            }
            else if ((req.bmRequestType & USB_U2_REQ_RCPT_MASK) == USB_U2_REQ_RCPT_ENDPOINT) {
                uint8_t ep = req.wIndex & 0xf;

                // series 2 don't have more than 5 endpoints (including 0)
                if (ep > 4)
                    break;

                UENUM = ep;
                status = ((UECONX & (1 << STALLRQ)) != 0) ? (1 << 0) : 0;
                UENUM = 0;
            }

            usb_u2_control_in((uint8_t*) &status, 2, false);
            break;
        }

        case USB_U2_REQ_CLEAR_FEATURE:  // FIXME: todo
        case USB_U2_REQ_SET_FEATURE:    // FIXME: todo
            break;

        case USB_U2_REQ_SET_ADDRESS: {
            if (((req.bmRequestType & USB_U2_REQ_DIR_MASK) == USB_U2_REQ_DIR_DEVICE_TO_HOST) ||
                ((req.bmRequestType & USB_U2_REQ_RCPT_MASK) != USB_U2_REQ_RCPT_DEVICE) ||
                (state != USB_U2_STATE_DEFAULT))
                break;

            UDADDR = req.wValue & 0x7f;
            usb_u2_control_out(NULL, 0);
            usb_u2_control_out_status();
            UDADDR |= (1 << ADDEN);
            state = USB_U2_STATE_ADDRESS;

            if (usb_u2_set_address_hook_cb != NULL)
                usb_u2_set_address_hook_cb(req.wValue & 0x7f);

            break;
        }

        case USB_U2_REQ_GET_DESCRIPTOR: {
            if (((req.bmRequestType & USB_U2_REQ_DIR_MASK) == USB_U2_REQ_DIR_HOST_TO_DEVICE) ||
                ((req.bmRequestType & USB_U2_REQ_RCPT_MASK) == USB_U2_REQ_RCPT_ENDPOINT))
                break;

            const void *addr = NULL;
            uint8_t len_offset = 0;

            switch (req.wValue >> 8) {
                case USB_U2_DESCR_TYPE_DEVICE:
                    addr = usb_u2_device_descriptor_cb();
                    break;

                case USB_U2_DESCR_TYPE_CONFIGURATION:
                    addr = usb_u2_config_descriptor_cb(config);
                    len_offset = 2;
                    break;

                case USB_U2_DESCR_TYPE_STRING:
                    addr = usb_u2_string_descriptor_cb(req.wValue, req.wIndex);
                    if (addr != NULL)
                        break;

                    switch ((uint8_t) req.wValue) {
                        case 0:
                            addr = &default_enus_lang;
                            break;

                        case USB_U2_DESCR_STR_IDX_SERIAL_INTERNAL: {
                            UEINTX &= ~(1 << RXSTPI);
                            while ((UEINTX & (1 << TXINI)) == 0);

                            UEDATX = 2 + (0x18 - 0x0e) * 4;
                            UEDATX = USB_U2_DESCR_TYPE_STRING;

                            // address range info from datasheet pag 236, table 23-6
                            for (uint8_t a = 0x0e; a < 0x18; a++) {
                                uint8_t b = boot_signature_byte_get(a);
                                UEDATX = (b >> 4) > 9 ? (b >> 4) - 10 + 'a' : (b >> 4) + '0';
                                UEDATX = 0;

                                // here we have the number of sent bytes as multiple of 8,
                                // that could be a IN packet boundary, lets check it.
                                if (UEBCLX >= ep0size) {
                                    UEINTX &= ~(1 << TXINI);
                                    while ((UEINTX & (1 << TXINI)) == 0);
                                }

                                UEDATX = (b & 0xf) > 9 ? (b & 0xf) - 10 + 'a' : (b & 0xf) + '0';
                                UEDATX = 0;
                            }

                            UEINTX &= ~(1 << TXINI);
                            while ((UEINTX & (1 << RXOUTI)) == 0);
                            UEINTX &= ~(1 << RXOUTI);

                            addr = NULL;
                        }
                    }
                    break;
            }

            if (addr == NULL)
                break;

            usb_u2_control_in(addr, pgm_read_byte_near(addr + len_offset), true);
            break;
        }

        case USB_U2_REQ_SET_DESCRIPTOR:     // FIXME: todo
        case USB_U2_REQ_GET_CONFIGURATION:  // FIXME: todo
            break;

        case USB_U2_REQ_SET_CONFIGURATION: {
            if (((req.bmRequestType & USB_U2_REQ_DIR_MASK) == USB_U2_REQ_DIR_DEVICE_TO_HOST) ||
                ((req.bmRequestType & USB_U2_REQ_RCPT_MASK) != USB_U2_REQ_RCPT_DEVICE) ||
                (state != USB_U2_STATE_ADDRESS))
                break;

            config = req.wValue;
            if (config > num_configs)
                break;

            usb_u2_control_out(NULL, 0);
            usb_u2_control_out_status();

            if (usb_u2_configure_endpoints_cb != NULL)
                usb_u2_configure_endpoints_cb(config);

            state = USB_U2_STATE_CONFIGURED;

            break;
        }

        case USB_U2_REQ_GET_INTERFACE:  // FIXME: todo
        case USB_U2_REQ_SET_INTERFACE:  // FIXME: todo
        case USB_U2_REQ_SYNCH_FRAME:    // FIXME: todo
            break;
    }

_stall:
    // interrupt not cleaned, stall ...
    UENUM = 0;
    if (UEINTX & (1 << RXSTPI)) {
        UECONX |= (1 << STALLRQ);
        UEINTX &= ~(1 << RXSTPI);
    }
}


void
usb_u2_configure_endpoint(const usb_u2_endpoint_descriptor_t *ep)
{
    if (ep == NULL)
        return;

    uint8_t epaddr = pgm_read_byte_near(&(ep->bEndpointAddress));
    uint8_t epnum = epaddr & 0xf;
    if (epnum != epmax + 1)
        return;
    epmax++;

    uint8_t eps = pgm_read_word_near(&(ep->wMaxPacketSize));

    UENUM = epnum;
    UECONX |= (1 << EPEN);
    UECFG0X = (pgm_read_byte_near(&(ep->bmAttributes)) << EPTYPE0) | (((epaddr & 0x80) ? 1 : 0) << EPDIR);
    UECFG1X = ((eps <= 8) ? 0 : ((eps <= 16) ? 1 : ((eps <= 32) ? 2 : 3)) << EPSIZE0) | (1 << ALLOC);
    UERST = (1 << EPRST0) | (1 << EPRST1) | (1 << EPRST2) | (1 << EPRST3) | (1 << EPRST4);
    UERST = 0;
    UENUM = 0;
}


void
usb_u2_task(void)
{
    UENUM = 0;
    if ((UEINTX & (1 << RXSTPI)) != 0)
        handle_ctrl();
}
