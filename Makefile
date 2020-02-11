# programmer and mcu settings
AVRDUDE_PROGRAMMER ?= usbtiny
AVRDUDE_PORT ?= usb
AVR_MCU ?= attiny4313
AVR_CPU_FREQUENCY ?= 20000000UL
USART_BREAK_TIME_US ?= 2500

AVRDUDE = avrdude
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

# disable clock/8, run with external clock
AVR_FUSE_LOW = 0xDF

# spi programming enabled
AVR_FUSE_HIGH_SPIEN = 0xDF
# debugwire enabled
AVR_FUSE_HIGH_DWEN = 0x5F

AVR_FUSE_EXTENDED = 0xFF
AVR_LOCKBIT = 0xFF

CFLAGS = \
	-std=gnu99 \
	-mmcu=$(AVR_MCU) \
	-DF_CPU=$(AVR_CPU_FREQUENCY) \
	-DUSART_BREAK_TIME_US=$(USART_BREAK_TIME_US) \
	-Os \
	-ggdb \
	-funsigned-char \
	-funsigned-bitfields \
	-fpack-struct \
	-fshort-enums \
	-fno-unit-at-a-time \
	-Wall \
	-Wno-implicit-fallthrough \
	-Wextra \
	-Werror \
	-I. \
	$(NULL)

SOURCES = \
	main.c \
	usart.c \
	usbdrv/usbdrv.c \
	usbdrv/usbdrvasm.S \
	$(NULL)

HEADERS = \
	usart.h \
	usbconfig.h \
	usbdrv/usbdrv.h \
	$(NULL)

all: firmware.hex

%.hex: %.elf
	$(OBJCOPY) \
		-O ihex \
		-j .data \
		-j .text \
		$< \
		$@

%.elf: $(SOURCES) $(HEADERS) Makefile
	$(CC) \
		$(CFLAGS) \
		$(SOURCES) \
		-o $@
	@$(MAKE) --no-print-directory size

size: firmware.elf
	@echo;$(SIZE) \
		--mcu=$(AVR_MCU) \
		-C $<

flash: firmware.hex
	$(AVRDUDE) \
		-p $(AVR_MCU) \
		-c $(AVRDUDE_PROGRAMMER) \
		-P $(AVRDUDE_PORT) \
		-U flash:w:$< \
		-U lfuse:w:$(AVR_FUSE_LOW):m \
		-U hfuse:w:$(AVR_FUSE_HIGH_SPIEN):m \
		-U efuse:w:$(AVR_FUSE_EXTENDED):m \
		-U lock:w:$(AVR_LOCKBIT):m

dw:
	$(AVRDUDE) \
		-p $(AVR_MCU) \
		-c $(AVRDUDE_PROGRAMMER) \
		-P $(AVRDUDE_PORT) \
		-U lfuse:w:$(AVR_FUSE_LOW):m \
		-U hfuse:w:$(AVR_FUSE_HIGH_DWEN):m \
		-U efuse:w:$(AVR_FUSE_EXTENDED):m \
		-U lock:w:$(AVR_LOCKBIT):m

clean:
	-$(RM) \
		firmware.elf \
		firmware.hex

.PHONY: all size flash dw clean
