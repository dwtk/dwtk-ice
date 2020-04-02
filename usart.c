/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD 3-Clause License.
 * See https://opensource.org/licenses/BSD-3-Clause.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "bits.h"
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
usart_send_break(uint16_t pulse_width)
{
    while (!(UCSRA & (1 << UDRE)));
    UCSRB &= ~(1 << TXEN);
    DDR_SET(P_TXD);
    PORT_CLEAR(P_TXD);
    while (pulse_width--) {
        // given our UCSZ and USBS settings:
        // - each frame is 1 start bit + 8 data bits + 1 stop bit = 10 bits
        // - each break is at least 2 frame errors, we send 3 = 30 bits
        //
        // cycles spent by the while loop and interruptions are ok. bigger
        // delays are fine, we just want to make sure that the break is sent.
        __builtin_avr_delay_cycles(30);
    }
    PORT_SET(P_TXD);
    DDR_CLEAR(P_TXD);
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
