/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the GPL-2 License.
 * See the file COPYING.
 */

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "usart.h"

#define DW_SPMEN (1 << 0)
#define DW_PGERS (1 << 1)
#define DW_PGWRT (1 << 2)
#define DW_RFLB  (1 << 3)
#define DW_CTPB  (1 << 4)

// https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_SPM.html
// opcode: 1001 0101 1110 1000
#define DW_SPM           0b1001010111101000

// https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_ADIW.html
// opcode: 1001 0110 KKdd KKKK
#define DW_ADIW_30_2     0b1001011000110010

// https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_OUT.html
// opcode: 1011 1AAr rrrr AAAA
// SPMCSR: 0x37
#define DW_OUT_SPMCSR_29 0b1011111111010111

#define uchar uint8_t
#include "usbdrv/usbdrv.h"

typedef enum {
    CMD_GET_ERROR = 0x40,
    CMD_GET_BAUDRATE_PRESCALER,
    CMD_DETECT_BAUDRATE,
    CMD_SET_BAUDRATE,
    CMD_DISABLE,
    CMD_RESET,
    CMD_GET_SIGNATURE,
    CMD_SEND_BREAK,
    CMD_RECV_BREAK,
    CMD_GO,
    CMD_STEP,
    CMD_CONTINUE,
    CMD_WAIT,
    CMD_WRITE_INSTRUCTION,
    CMD_SET_PC,
    CMD_GET_PC,
    CMD_REGISTERS,
    CMD_SRAM,
    CMD_READ_FLASH,
    CMD_WRITE_FLASH_PAGE,
    CMD_ERASE_FLASH_PAGE,
} usb_command_t;

typedef enum {
    ERR_NONE = 0,
    ERR_BAUDRATE_DETECTION,
    ERR_ECHO_MISMATCH,
    ERR_BREAK_MISMATCH,
    ERR_TOO_LARGE,
} error_type_t;

static bool after_break = false;
static uint16_t ubrr = 0xffff;
static uint16_t flash_page_start = 0;
static uint16_t request_len = 0;
static const uint8_t freq_mhz = F_CPU / 1000000;
static volatile bool data_on = false;
static volatile uint16_t remaining = 0;
static volatile usb_command_t cmd;

// this is defined by the biggest flash page size we support, that is 128 bytes.
// it is also limited by the SRAM size of the ATtiny4313. if we want to support
// any device with bigger flash page size, we will need to implement partial
// read/write from the host. This is kinda tricky, specially for reads, because
// the devices won't wait too long for data reads.
static uint8_t alloc[129] = {
    ERR_NONE,
};
static uint8_t *err = alloc;
static uint8_t *buf = alloc + 1;


static void
read_usart_to_buffer(uint16_t len)
{
    if (*err != ERR_NONE) {
        return;
    }
    if (len > 128) {
        *err = ERR_TOO_LARGE;
        return;
    }
    for (uint8_t i = 0; i < len; i++) {
        buf[i] = usart_recv_byte();
    }
}


void  // not static because we "call" it from usbconfig.h
data_led_on(void)
{
    data_on = true;;
    PORTD |= (1 << 6);
}


static void
data_led_off(void)
{
    if (data_on) {
        data_on = false;
        PORTD &= ~(1 << 6);
    }
}


static void
detect_baudrate(void)
{
    usart_clean();
    usart_init(0);

    uint8_t last = 0xff;
    for (uint8_t i = 20; i > 0; i--) {
        uint8_t tmp_ubrr = ((freq_mhz * 8) - i) / i;
        if (tmp_ubrr == last) {
            continue;
        }
        wdt_reset();
        usart_clean();
        usart_init(tmp_ubrr);
        usart_send_break();
        if (0x55 == usart_recv_break_with_timeout(0xff)) {
            ubrr = tmp_ubrr;
            return;
        }
        last = tmp_ubrr;
    }

    *err = ERR_BAUDRATE_DETECTION;
    ubrr = 0xffff;
}


static void
send_byte(uint8_t b)
{
    if (*err != ERR_NONE) {
        return;
    }
    usart_send_byte(b);
    uint8_t c = usart_recv_byte();
    if (b != c) {
        *err = ERR_ECHO_MISMATCH;
    }
}


static void
recv_break()
{
    if (*err != ERR_NONE) {
        return;
    }
    wdt_reset();
    uint8_t c = usart_recv_break();
    if (c != 0x55) {
        *err = ERR_BREAK_MISMATCH;
    }
    else {
        after_break = true;
    }
}


static void
send_break()
{
    if (*err != ERR_NONE) {
        return;
    }
    usart_send_break();
    recv_break();
}


static void
registers(uint8_t start, uint8_t len, bool write)
{
    if (*err != ERR_NONE)
        return;

    send_byte(0x66);
    send_byte(0xd0);
    send_byte(0x00);
    send_byte(start);
    send_byte(0xd1);
    send_byte(0x00);
    send_byte(start + len);
    send_byte(0xc2);
    send_byte(write ? 0x05 : 0x01);
    send_byte(0x20);
}


static void
write_instruction(uint16_t inst)
{
    if (*err != ERR_NONE)
        return;

    send_byte(0x64);
    send_byte(0xd2);
    send_byte(inst >> 8);
    send_byte(inst);
    send_byte(0x23);
}


static void
erase_flash_page(uint16_t start, bool set_start)
{
    if (*err != ERR_NONE)
        return;

    registers(29, set_start ? 3 : 1, true);
    send_byte(DW_PGERS | DW_SPMEN);
    if (set_start) {
        send_byte(start);
        send_byte(start >> 8);
    }
    write_instruction(DW_OUT_SPMCSR_29);
    write_instruction(DW_SPM);
    send_break();
}


usbMsgLen_t
usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void*) data;
    bool write = (rq->bmRequestType & USBRQ_DIR_MASK) == USBRQ_DIR_HOST_TO_DEVICE;
    usbMsgLen_t rv = 1;  // err, always return err + buf unless USB_NO_MSG

    cmd = rq->bRequest;

    switch (cmd) {
        // these are the only commands that support writing
        case CMD_REGISTERS:
        case CMD_SRAM:
        case CMD_WRITE_FLASH_PAGE:
            break;

        default:
            if (write) {
                return 0;
            }
    }

    if (cmd != CMD_GET_ERROR) {
        *err = ERR_NONE;
    }

    request_len = rq->wLength.word;
    if (request_len > 0 && !write) {
        request_len--;
    }
    remaining = request_len;

    switch (cmd) {
        case CMD_GET_ERROR: {
            // nothing to do, buffer is already filled with error and rv already set
            break;
        }

        case CMD_GET_BAUDRATE_PRESCALER: {
            buf[0] = 16;
            buf[1] = freq_mhz;
            rv += 2;
            break;
        }

        case CMD_DETECT_BAUDRATE: {
            detect_baudrate();
            buf[0] = ubrr >> 8;
            buf[1] = ubrr;
            rv += 2;
            break;
        }

        case CMD_SET_BAUDRATE: {
            ubrr = rq->wValue.word;
            usart_clean();
            usart_init(ubrr);
            send_break();
            break;
        }

        case CMD_DISABLE: {
            send_byte(0x06);
            break;
        }

        case CMD_RESET: {
            send_break();
            send_byte(0x07);
            recv_break();
            break;
        }

        case CMD_GET_SIGNATURE: {
            send_byte(0xf3);
            buf[0] = usart_recv_byte();
            buf[1] = usart_recv_byte();
            rv += 2;
            break;
        }

        case CMD_SEND_BREAK: {
            send_break();
            break;
        }

        case CMD_RECV_BREAK: {
            recv_break();
            break;
        }

        case CMD_GO: {
            send_byte(0x40);
            send_byte(0x30);
            break;
        }

        case CMD_STEP: {
            send_byte(0x60);
            send_byte(0x31);
            recv_break();
            break;
        }

        case CMD_CONTINUE: {
            // idx: byte 0 -> hw bp set
            //      byte 1 -> timers
            uint8_t t = 0x60;
            if (rq->wIndex.word & (1 << 0)) {
                t = 0x61;
                send_byte(0xd1);
                uint8_t bp = rq->wValue.word / 2;
                send_byte(bp >> 8);
                send_byte(bp);
            }
            if (rq->wIndex.word & (1 << 1)) {
                t -= 0x20;
            }
            send_byte(t);
            send_byte(0x30);
            break;
        }

        case CMD_WAIT: {
            buf[0] = usart_wait() ? 0xff : 0;
            rv++;
            break;
        }

        case CMD_WRITE_INSTRUCTION: {
            write_instruction(rq->wValue.word);
            break;
        }

        case CMD_SET_PC: {
            send_byte(0xd0);
            uint8_t b = rq->wValue.word / 2;
            send_byte(b >> 8);
            send_byte(b);
            after_break = false;
            break;
        }

        case CMD_GET_PC: {
            send_byte(0xf0);
            uint16_t b = usart_recv_byte() << 8;
            b |= usart_recv_byte();
            if (after_break) {
                b--;
                after_break = false;
            }
            b *= 2;
            buf[0] = b >> 8;
            buf[1] = b;
            rv += 2;
            break;
        }

        case CMD_REGISTERS: {
            registers(rq->wValue.word, request_len, write);
            if (write) {
                return USB_NO_MSG;
            }
            read_usart_to_buffer(request_len);
            rv += request_len;
            break;
        }

        case CMD_SRAM: {
            registers(30, 2, true);
            send_byte(rq->wValue.word);
            send_byte(rq->wValue.word >> 8);
            uint16_t l = request_len * 2;
            if (write) {
                l++;
            }
            send_byte(0x66);
            send_byte(0xd0);
            send_byte(0x00);
            send_byte(write ? 0x01 : 0x00);
            send_byte(0xd1);
            send_byte(l >> 8);
            send_byte(l);
            send_byte(0xc2);
            send_byte(write ? 0x04 : 0x00);
            send_byte(0x20);
            if (write) {
                return USB_NO_MSG;
            }
            read_usart_to_buffer(request_len);
            rv += request_len;
            break;
        }

        case CMD_READ_FLASH: {
            registers(30, 2, true);
            send_byte(rq->wValue.word);
            send_byte(rq->wValue.word >> 8);
            uint16_t l = request_len * 2;
            send_byte(0x66);
            send_byte(0xd0);
            send_byte(0x00);
            send_byte(0x00);
            send_byte(0xd1);
            send_byte(l >> 8);
            send_byte(l);
            send_byte(0xc2);
            send_byte(0x02);
            send_byte(0x20);
            read_usart_to_buffer(request_len);
            rv += request_len;
            break;
        }

        case CMD_WRITE_FLASH_PAGE: {
            registers(29, 3, true);
            send_byte(DW_CTPB | DW_SPMEN);
            send_byte(rq->wValue.word);
            send_byte(rq->wValue.word >> 8);
            write_instruction(DW_OUT_SPMCSR_29);
            write_instruction(DW_SPM);
            send_break();

            erase_flash_page(0, false);

            registers(29, 1, true);
            send_byte(DW_SPMEN);

            flash_page_start = rq->wValue.word;
            return USB_NO_MSG;
        }

        case CMD_ERASE_FLASH_PAGE: {
            erase_flash_page(rq->wValue.word, true);
            break;
        }
    }

    usbMsgPtr = alloc;

    return rv;
}


uchar
usbFunctionWrite(uchar *data, uchar len)
{
    wdt_reset();
    for (uint8_t i = 0; i < len && remaining; i++, remaining--) {
        buf[request_len - remaining] = data[i];
    }

    if (remaining) {
        return 0;
    }

    switch (cmd) {
        case CMD_REGISTERS:
        case CMD_SRAM: {
            uint8_t i = 0;
            wdt_reset();
            while (i < request_len) {
                send_byte(buf[i++]);
            }
            break;
        }

        case CMD_WRITE_FLASH_PAGE: {
            uint8_t i = 0;
            while (i < request_len) {
                wdt_reset();
                registers(0, 2, true);
                send_byte(buf[i++]);
                send_byte(buf[i++]);
                write_instruction(DW_OUT_SPMCSR_29);
                write_instruction(DW_SPM);
                write_instruction(DW_ADIW_30_2);
            }

            wdt_reset();
            registers(29, 3, true);
            send_byte(DW_PGWRT | DW_SPMEN);
            send_byte(flash_page_start);
            send_byte(flash_page_start >> 8);
            write_instruction(DW_OUT_SPMCSR_29);
            write_instruction(DW_SPM);
            send_break();
            break;
        }

        default:
            break;
    }

    return 1;
}


int
main(void)
{
    wdt_enable(WDTO_1S);

    DDRD |= (1 << 5) | (1 << 6);

    usbInit();
    usbDeviceDisconnect();

    uint8_t i = 0xff;
    while (i--) {
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();

    sei();

    for (;;) {
        wdt_reset();
        usbPoll();
        data_led_off();
    }

    return 0;
}
