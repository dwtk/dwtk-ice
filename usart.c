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
usart_clean(void)
{
    while (!(UCSRA & (1 << UDRE)));
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


uint16_t
usart_recv_byte_with_timeout(void)
{
    uint16_t t = 0xffff;
    while (t-- && !(UCSRA & (1 << RXC)));
    if (t == 0) {
        return 0xff00;
    }
    return UDR;
}


void
usart_send_break(void)
{
    while (!(UCSRA & (1 << UDRE)));
    UCSRB &= ~(1 << TXEN);
    DDRD |= (1 << 1);
    PORTD &= ~(1 << 1);
    _delay_ms(5);
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


uint8_t
usart_recv_break_with_timeout(void)
{
    uint8_t rv = 0;
    uint8_t t = 0xff;
    while (t--) {
        uint8_t status;
        uint16_t t1 = 0xffff;
        while (t1-- && !((status = UCSRA) & (1 << RXC)));
        if (!t1) {
            return 0;
        }
        rv = UDR;
        if (!(status & (1 << FE))) {
            break;
        }
    }
    return t ? rv : 0;
}
