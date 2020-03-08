#
# dwtk-makefile: A generic Makefile for AVR projects using dwtk.
# Copyright (C) 2020 Rafael G. Martins <rafael@rafaelmartins.eng.br>
#
# This program can be distributed under the terms of the BSD 3-Clause License.
# See https://opensource.org/licenses/BSD-3-Clause.
#

### Main settings

# The target AVR microcontroller
AVR_MCU ?= attiny4313

# The frequency of the AVR microcontroller. Must match the actual operating
# clock of the microcontroller, otherwise the delay functions won't work as
# expected.
AVR_F_CPU ?= 20000000UL


### Fuses (only usable with SPI-capable dwtk-ice hardware)

# Low fuse. Should be configured according to the hardware clock.
AVR_LFUSE ?= 0xDF

# High fuse. This value must have the SPIEN bit programmed, otherwise it is
# impossible to disable debugWIRE.
AVR_HFUSE ?= 0xDF

# Extended fuse. Usually not changed. It is safe to keep this commented out.
#AVR_EFUSE ?= 0xFF

# Lock bits. Used to prevent further programming and verification of the chip.
# After programming such bits, it may be necessary to erase the chip to
# unprogram them. Usually not changed. It is safe to keep this commented out.
#AVR_LOCK ?= 0xFF


### Firmware specific settings

USART_BREAK_TIME_US ?= 2500

# Firmware name. The filename (without extension) of the firmware.
FIRMWARE_NAME ?= dwtk-ice

# Firmware CFLAGS. The CFLAGS needed to build the firmware. Usually contains
# include paths and gcc arguments to disable warnings. The Makefile converts
# any warnings into compilation errors. If some warning must be ignored, the
# specific gcc argument.
FIRMWARE_CFLAGS = \
	-I. \
	-DUSART_BREAK_TIME_US=$(USART_BREAK_TIME_US) \
	$(NULL)

# Firmware sources. The source files (C), that should be built into the
# firmware, relative to the directory containing the Makefile.
FIRMWARE_SOURCES = \
	main.c \
	usart.c \
	usbdrv/usbdrv.c \
	usbdrv/usbdrvasm.S \
	$(NULL)

# Firmware headers. The source headers (C), that should be built into the
# firmware, relative to the directory containing the Makefile.
FIRMWARE_HEADERS = \
	bits.h \
	usart.h \
	usbconfig.h \
	usbdrv/usbdrv.h \
	$(NULL)
