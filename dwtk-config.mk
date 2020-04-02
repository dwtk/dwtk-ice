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
