AVR_MCU   ?= attiny4313
AVR_LFUSE ?= 0xDF
AVR_HFUSE ?= 0xDF

FIRMWARE_NAME ?= dwtk-ice

FIRMWARE_CFLAGS = \
	-I. \
	$(NULL)

FIRMWARE_SOURCES = \
	main.c \
	usart.c \
	$(NULL)

FIRMWARE_HEADERS = \
	bits.h \
	usart.h \
	$(NULL)

ifeq ($(AVR_MCU),$(filter $(AVR_MCU),atmega8u2 atmega16u2 atmega32u2))
AVR_F_CPU ?= 16000000UL
AVR_EFUSE ?= 0xFF

FIRMWARE_SOURCES += \
	usb_u2_descriptors.c \
	usb-u2/usb-u2.c \
	$(NULL)

FIRMWARE_HEADERS += \
	usb-u2/usb-u2.h \
	$(NULL)
else
AVR_F_CPU ?= 20000000UL

FIRMWARE_SOURCES += \
	usbdrv/usbdrv.c \
	usbdrv/usbdrvasm.S \
	$(NULL)

FIRMWARE_HEADERS += \
	usbconfig.h \
	usbdrv/usbdrv.h \
	$(NULL)

write-serial-number: .check-dwtk
	SN="$$((RANDOM % 256)) $$((RANDOM % 256)) $$((RANDOM % 256)) $$((RANDOM % 256))"; \
	printf "\nSerial number: %02x%02x%02x%02x\n" $${SN}; \
	$(DWTK_CMD) eeprom-bytes $${SN}

.PHONY: write-serial-number
endif
