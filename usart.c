/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD 3-Clause License.
 * See https://opensource.org/licenses/BSD-3-Clause.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"


void
usart_init(uint16_t baudrate)
{
    UBRRH = (uint8_t) (baudrate >> 8);
    UBRRL = (uint8_t) baudrate;
    UCSRA = (1 << U2X);
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (0b11 << UCSZ0);
}


void
usart_clear(void)
{
    UBRRH = 0;
    UBRRL = 0;
    UCSRA = 0;
    UCSRB = 0;
    UCSRC = 0;
}


void
usart_send_byte(uint8_t b)
{
    while (!(UCSRA & (1 << UDRE)));
    UCSRA |= (1 << TXC);  // clean TXC
    UDR = b;
    while (!(UCSRA & (1 << TXC)));
}


uint8_t
usart_recv_byte(void)
{
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}


void
usart_send_break(void)
{
    while (!(UCSRA & (1 << UDRE)));
    UCSRB &= ~(1 << TXEN);
    DDRD |= (1 << 1);
    PORTD &= ~(1 << 1);
    _delay_us(USART_BREAK_TIME_US);
    PORTD |= (1 << 1);
    DDRD &= ~(1 << 1);
    UCSRB |= (1 << TXEN);
}


uint8_t
usart_recv_break(void)
{
    uint8_t rv = 0;
    for (;;) {
        uint8_t status;
        while (!((status = UCSRA) & (1 << RXC)));
        rv = UDR;
        if (!(status & (1 << FE))) {
            break;
        }
    }
    return rv;
}
