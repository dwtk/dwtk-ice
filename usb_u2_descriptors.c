#include <avr/pgmspace.h>
#include <stddef.h>
#include <stdint.h>
#include "usb-u2/usb-u2.h"


static const usb_u2_device_descriptor_t device_descriptor PROGMEM = {
    .bLength            = sizeof(usb_u2_device_descriptor_t),
    .bDescriptorType    = USB_U2_DESCR_TYPE_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = USB_U2_DESCR_DEV_CLASS_VENDOR_SPEC,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize0    = 64,
    .idVendor           = 0x1d50,
    .idProduct          = 0x614c,
    .bcdDevice          = 0,
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = USB_U2_DESCR_STR_IDX_SERIAL_INTERNAL,
    .bNumConfigurations = 1,
};

const usb_u2_device_descriptor_t*
usb_u2_device_descriptor_cb(void)
{
    return &device_descriptor;
}


typedef struct {
    usb_u2_config_descriptor_t    config_descriptor;
    usb_u2_interface_descriptor_t vendor_interface;
} __attribute__((packed)) config_descriptor_t;

static const config_descriptor_t config_descriptor PROGMEM = {
    .config_descriptor = {
        .bLength             = sizeof(usb_u2_config_descriptor_t),
        .bDescriptorType     = USB_U2_DESCR_TYPE_CONFIGURATION,
        .wTotalLength        = sizeof(config_descriptor_t),
        .bNumInterfaces      = 1,
        .bConfigurationValue = 1,
        .iConfiguration      = 0,
        .bmAttributes        = (1 << 7),
        .bMaxPower           = 50,
    },
    .vendor_interface = {
        .bLength            = sizeof(usb_u2_interface_descriptor_t),
        .bDescriptorType    = USB_U2_DESCR_TYPE_INTERFACE,
        .bInterfaceNumber   = 0,
        .bAlternateSetting  = 0,
        .bNumEndpoints      = 0,
        .bInterfaceClass    = 0,
        .bInterfaceSubClass = 0,
        .bInterfaceProtocol = 0,
        .iInterface         = 0,
    },
};

const usb_u2_config_descriptor_t*
usb_u2_config_descriptor_cb(uint8_t config_id)
{
    (void) config_id;
    return &(config_descriptor.config_descriptor);
}


#define MANUFACTURER L"dwtk.rgm.io"
#define PRODUCT L"dwtk-ice"

static const usb_u2_string_descriptor_t manufacturer PROGMEM = {
    .bLength = sizeof(MANUFACTURER),
    .bDescriptorType = USB_U2_DESCR_TYPE_STRING,
    .wData = MANUFACTURER,
};

static const usb_u2_string_descriptor_t product PROGMEM = {
    .bLength = sizeof(PRODUCT),
    .bDescriptorType = USB_U2_DESCR_TYPE_STRING,
    .wData = PRODUCT,
};

const usb_u2_string_descriptor_t*
usb_u2_string_descriptor_cb(uint8_t string_id, uint16_t lang_id)
{
    (void) lang_id;

    switch (string_id) {
        case 1:
            return &manufacturer;
        case 2:
            return &product;
    }
    return NULL;
}
