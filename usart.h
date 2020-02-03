/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD 3-Clause License.
 * See https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

void usart_init(uint16_t baudrate);
void usart_clear(void);
void usart_send_byte(uint8_t b);
uint8_t usart_recv_byte(void);
void usart_send_break(void);
uint8_t usart_recv_break(void);
