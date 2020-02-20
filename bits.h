/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD 3-Clause License.
 * See https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#define P_USCK (B, 7)
#define P_DI   (B, 5)
#define P_DO   (B, 6)
#define P_TXD  (D, 1)
#define P_LEDR (D, 5)
#define P_LEDG (B, 0)

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
