AVR_MCU   ?= attiny4313
AVR_F_CPU ?= 20000000UL
AVR_LFUSE ?= 0xDF
AVR_HFUSE ?= 0xDF

FIRMWARE_NAME ?= dwtk-ice

FIRMWARE_CFLAGS = \
	-I. \
	$(NULL)

FIRMWARE_SOURCES = \
	main.c \
	usart.c \
	usbdrv/usbdrv.c \
	usbdrv/usbdrvasm.S \
	$(NULL)

FIRMWARE_HEADERS = \
	bits.h \
	usart.h \
	usbconfig.h \
	usbdrv/usbdrv.h \
	$(NULL)

write-serial-number: .check-dwtk
	SN="$$((RANDOM % 256)) $$((RANDOM % 256)) $$((RANDOM % 256)) $$((RANDOM % 256))"; \
	printf "\nSerial number: %02x%02x%02x%02x\n" $${SN}; \
	$(DWTK_CMD) eeprom-bytes $${SN}

.PHONY: write-serial-number
