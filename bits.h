/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD 3-Clause License.
 * See https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#ifndef TIFR
#define TIFR TIFR0
#endif
#ifndef UCSRA
#define UCSRA UCSR0A
#endif
#ifndef UCSRB
#define UCSRB UCSR0B
#endif
#ifndef UCSRC
#define UCSRC UCSR0C
#endif
#ifndef UCSZ0
#define UCSZ0 UCSZ00
#endif
#ifndef UBRRL
#define UBRRL UBRR0L
#endif
#ifndef UBRRH
#define UBRRH UBRR0H
#endif
#ifndef RXEN
#define RXEN RXEN0
#endif
#ifndef TXEN
#define TXEN TXEN0
#endif
#ifndef RXC
#define RXC RXC0
#endif
#ifndef TXC
#define TXC TXC0
#endif
#ifndef UDR
#define UDR UDR0
#endif
#ifndef UDRE
#define UDRE UDRE0
#endif
#ifndef FE
#define FE FE0
#endif
#ifndef U2X
#define U2X U2X0
#endif

#ifdef __AVR_ATtiny4313__
#define P_USCK    (B, 7)
#define P_DI      (B, 5)
#define P_DO      (B, 6)
#define P_TXD     (D, 1)
#define P_LEDR    (D, 5)
#define P_LEDG    (B, 0)
#define P_CAP_SPI (B, 4)
#else
#define P_USCK    (B, 5)
#define P_DI      (B, 4)
#define P_DO      (B, 3)
#define P_TXD     (D, 1)
#define P_LEDR    (D, 7)
#define P_LEDG    (B, 1)
#define P_CAP_SPI (C, 0)
#endif

#define BIT_SET(reg, bit)   {(reg) |=  (1 << bit);}
#define BIT_CLEAR(reg, bit) {(reg) &= ~(1 << bit);}
#define BIT_TEST(reg, bit)  ((reg) &   (1 << bit))

#define _DDR_SET(port, bit)    BIT_SET(DDR ## port, bit)
#define _DDR_CLEAR(port, bit)  BIT_CLEAR(DDR ## port, bit)
#define _PORT_SET(port, bit)   BIT_SET(PORT ## port, bit)
#define _PORT_CLEAR(port, bit) BIT_CLEAR(PORT ## port, bit)
#define _PIN_TEST(port, bit)   BIT_TEST(PIN ## port, bit)

#define DDR_SET(p)    _DDR_SET p
#define DDR_CLEAR(p)  _DDR_CLEAR p
#define PORT_SET(p)   _PORT_SET p
#define PORT_CLEAR(p) _PORT_CLEAR p
#define PIN_TEST(p)   _PIN_TEST p
