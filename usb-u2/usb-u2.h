/*
 * usb-u2: A bare minimum USB stack for atmega{8,16,32}u2.
 *
 * SPDX-FileCopyrightText: 2021-2022 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Request (Setup) data macros

#define USB_U2_REQ_DIR_HOST_TO_DEVICE (0 << 7)
#define USB_U2_REQ_DIR_DEVICE_TO_HOST (1 << 7)
#define USB_U2_REQ_DIR_MASK           (1 << 7)

#define USB_U2_REQ_TYPE_STANDARD      (0 << 5)
#define USB_U2_REQ_TYPE_CLASS         (1 << 5)
#define USB_U2_REQ_TYPE_VENDOR        (2 << 5)
#define USB_U2_REQ_TYPE_MASK          (3 << 5)

#define USB_U2_REQ_RCPT_DEVICE        (0 << 0)
#define USB_U2_REQ_RCPT_INTERFACE     (1 << 0)
#define USB_U2_REQ_RCPT_ENDPOINT      (2 << 0)
#define USB_U2_REQ_RCPT_OTHER         (3 << 0)
#define USB_U2_REQ_RCPT_MASK          (3 << 0)

#define USB_U2_REQ_GET_STATUS         0x00
#define USB_U2_REQ_CLEAR_FEATURE      0x01
#define USB_U2_REQ_SET_FEATURE        0x03
#define USB_U2_REQ_SET_ADDRESS        0x05
#define USB_U2_REQ_GET_DESCRIPTOR     0x06
#define USB_U2_REQ_SET_DESCRIPTOR     0x07
#define USB_U2_REQ_GET_CONFIGURATION  0x08
#define USB_U2_REQ_SET_CONFIGURATION  0x09
#define USB_U2_REQ_GET_INTERFACE      0x0a
#define USB_U2_REQ_SET_INTERFACE      0x0b
#define USB_U2_REQ_SYNCH_FRAME        0x0c


// Descriptor macros

#define USB_U2_DESCR_TYPE_DEVICE                      0x01
#define USB_U2_DESCR_TYPE_CONFIGURATION               0x02
#define USB_U2_DESCR_TYPE_STRING                      0x03
#define USB_U2_DESCR_TYPE_INTERFACE                   0x04
#define USB_U2_DESCR_TYPE_ENDPOINT                    0x05
#define USB_U2_DESCR_TYPE_DEVICE_QUALIFIER            0x06
#define USB_U2_DESCR_TYPE_OTHER_SPEED_CONFIGURATION   0x07

#define USB_U2_DESCR_CONFIG_ATTR_RESERVED             (1 << 7)
#define USB_U2_DESCR_CONFIG_ATTR_SELF_POWERED         (1 << 6)
#define USB_U2_DESCR_CONFIG_ATTR_REMOTE_WAKEUP        (1 << 5)

#define USB_U2_DESCR_DEV_CLASS_PER_INTERFACE          0x00
#define USB_U2_DESCR_DEV_CLASS_AUDIO                  0x01
#define USB_U2_DESCR_DEV_CLASS_COMM                   0x02
#define USB_U2_DESCR_DEV_CLASS_HID                    0x03
#define USB_U2_DESCR_DEV_CLASS_PHYSICAL               0x05
#define USB_U2_DESCR_DEV_CLASS_STILL_IMAGE            0x06
#define USB_U2_DESCR_DEV_CLASS_PRINTER                0x07
#define USB_U2_DESCR_DEV_CLASS_MASS_STORAGE           0x08
#define USB_U2_DESCR_DEV_CLASS_HUB                    0x09
#define USB_U2_DESCR_DEV_CLASS_CDC_DATA               0x0a
#define USB_U2_DESCR_DEV_CLASS_CSCID                  0x0b
#define USB_U2_DESCR_DEV_CLASS_CONTENT_SEC            0x0d
#define USB_U2_DESCR_DEV_CLASS_VIDEO                  0x0e
#define USB_U2_DESCR_DEV_CLASS_WIRELESS_CONTROLLER    0xe0
#define USB_U2_DESCR_DEV_CLASS_PERSONAL_HEALTHCARE    0x0f
#define USB_U2_DESCR_DEV_CLASS_AUDIO_VIDEO            0x10
#define USB_U2_DESCR_DEV_CLASS_BILLBOARD              0x11
#define USB_U2_DESCR_DEV_CLASS_USB_TYPE_C_BRIDGE      0x12
#define USB_U2_DESCR_DEV_CLASS_MISC                   0xef
#define USB_U2_DESCR_DEV_CLASS_APP_SPEC               0xfe
#define USB_U2_DESCR_DEV_CLASS_VENDOR_SPEC            0xff
#define USB_U2_DESCR_DEV_SUBCLASS_VENDOR_SPEC         0xff

#define USB_U2_DESCR_EPT_ADDR_DIR_OUT                 (0 << 7)
#define USB_U2_DESCR_EPT_ADDR_DIR_IN                  (1 << 7)
#define USB_U2_DESCR_EPT_ADDR_DIR_MASK                (1 << 7)

#define USB_U2_DESCR_EPT_ATTR_CONTROL                 (0 << 0)
#define USB_U2_DESCR_EPT_ATTR_ISOCHRONOUS             (1 << 0)
#define USB_U2_DESCR_EPT_ATTR_BULK                    (2 << 0)
#define USB_U2_DESCR_EPT_ATTR_INTERRUPT               (3 << 0)
#define USB_U2_DESCR_EPT_ATTR_NO_SYNC                 (0 << 2)
#define USB_U2_DESCR_EPT_ATTR_ASYNC                   (1 << 2)
#define USB_U2_DESCR_EPT_ATTR_ADAPTIVE                (2 << 2)
#define USB_U2_DESCR_EPT_ATTR_SYNC                    (3 << 2)
#define USB_U2_DESCR_EPT_ATTR_DATA                    (0 << 4)
#define USB_U2_DESCR_EPT_ATTR_FEEDBACK                (1 << 2)
#define USB_U2_DESCR_EPT_ATTR_IMPLICIT_FEEDBACK_DATA  (2 << 2)

#define USB_U2_DESCR_STR_IDX_SERIAL_INTERNAL          0xff


// Feature selector macros

#define USB_U2_FEAT_ENDPOINT_HALT                     0x00
#define USB_U2_FEAT_DEVICE_REMOTE_WAKEUP              0x01
#define USB_U2_FEAT_TEST_MODE                         0x02


// USB state macros

#define USB_U2_STATE_DEFAULT    0
#define USB_U2_STATE_ADDRESS    1
#define USB_U2_STATE_CONFIGURED 2


// Request (setup) types

typedef struct {
    uint8_t  bmRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} __attribute__((packed)) usb_u2_control_request_t;


// Descriptor types

typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
} __attribute__((packed)) usb_u2_device_descriptor_t;

typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  bMaxPower;
} __attribute__((packed)) usb_u2_config_descriptor_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    int16_t wData[];
} __attribute__((packed)) usb_u2_string_descriptor_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __attribute__((packed)) usb_u2_interface_descriptor_t;

typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;
    uint8_t  bRefresh;       // audio endpoints only
    uint8_t  bSynchAddress;  // audio endpoints only
} __attribute__((packed)) usb_u2_endpoint_descriptor_t;


// Library API
void usb_u2_init(void);
void usb_u2_task(void);
void usb_u2_configure_endpoint(const usb_u2_endpoint_descriptor_t *ep);
uint8_t usb_u2_control_in(const uint8_t *b, size_t len, bool from_progmem);
uint8_t usb_u2_control_out(uint8_t *b, size_t len);
void usb_u2_control_out_status(void);
void usb_u2_endpoint_select(uint8_t ep);
bool usb_u2_endpoint_in_ready(void);
uint8_t usb_u2_endpoint_in(const uint8_t *b, size_t len);
bool usb_u2_endpoint_out_received(void);
uint8_t usb_u2_endpoint_out(uint8_t *data, uint8_t len);


// Callbacks
const usb_u2_device_descriptor_t* usb_u2_device_descriptor_cb(void);
const usb_u2_config_descriptor_t* usb_u2_config_descriptor_cb(uint8_t config_id);
const usb_u2_string_descriptor_t* usb_u2_string_descriptor_cb(uint8_t string_id, uint16_t lang_id);
void usb_u2_configure_endpoints_cb(uint8_t config_id) __attribute__((weak));
void usb_u2_control_vendor_cb(const usb_u2_control_request_t *req) __attribute__((weak));
void usb_u2_reset_hook_cb(void) __attribute__((weak));
void usb_u2_set_address_hook_cb(uint8_t addr) __attribute__((weak));
