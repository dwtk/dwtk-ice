AVR_MCU   ?= attiny4313
AVR_F_CPU ?= 20000000UL
AVR_LFUSE ?= 0xDF
AVR_HFUSE ?= 0xDF

USART_BREAK_TIME_US ?= 2500

FIRMWARE_NAME ?= dwtk-ice

FIRMWARE_CFLAGS = \
	-I. \
	-DUSART_BREAK_TIME_US=$(USART_BREAK_TIME_US) \
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
