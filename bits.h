/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD 3-Clause License.
 * See https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#if defined(__AVR_ATtiny4313__)

#define P_USCK    (B, 7)
#define P_DI      (B, 5)
#define P_DO      (B, 6)
#define P_TXD     (D, 1)
#define P_LEDR    (D, 5)
#define P_LEDG    (B, 0)
#define P_CAP_SPI (B, 4)

#elif defined(__AVR_ATmega8U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__)

#define TIFR TIFR1
#define UCSRA UCSR1A
#define UCSRB UCSR1B
#define UCSRC UCSR1C
#define UCSZ0 UCSZ10
#define UBRRL UBRR1L
#define UBRRH UBRR1H
#define RXEN RXEN1
#define TXEN TXEN1
#define RXC RXC1
#define TXC TXC1
#define UDR UDR1
#define UDRE UDRE1
#define FE FE1
#define U2X U2X1

#define P_USCK    (B, 1)
#define P_DI      (B, 3)
#define P_DO      (B, 2)
#define P_SS      (B, 0)
#define P_TXD     (D, 3)
#define P_LEDR    (C, 2)
#define P_LEDG    (D, 0)
#define P_CAP_SPI (B, 4)

#else

#define TIFR TIFR1
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define UCSZ0 UCSZ00
#define UBRRL UBRR0L
#define UBRRH UBRR0H
#define RXEN RXEN0
#define TXEN TXEN0
#define RXC RXC0
#define TXC TXC0
#define UDR UDR0
#define UDRE UDRE0
#define FE FE0
#define U2X U2X0

#define P_USCK    (B, 5)
#define P_DI      (B, 4)
#define P_DO      (B, 3)
#define P_SS      (B, 2)
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
