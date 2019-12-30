/*
 * dwtk-ice: An USB-connected In-Circuit Emulator for dwtk.
 * Copyright (C) 2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the GPL-2 License.
 * See the file COPYING.
 */

#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "usart.h"

#define DW_SPMEN (1 << 0)
#define DW_PGERS (1 << 1)
#define DW_PGWRT (1 << 2)
#define DW_RFLB  (1 << 3)
#define DW_CTPB  (1 << 4)

// https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_SPM.html
// opcode: 1001 0101 1110 1000
#define DW_SPM           0b1001010111101000

// https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_ADIW.html
// opcode: 1001 0110 KKdd KKKK
#define DW_ADIW_30_2     0b1001011000110010

// https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_OUT.html
// opcode: 1011 1AAr rrrr AAAA
// SPMCSR: 0x37
#define DW_OUT_SPMCSR_29 0b1011111111010111

#define uchar uint8_t
#include "usbdrv/usbdrv.h"

#if F_CPU == 20000000
static const uint8_t ubrr_values[] = {
    0x07,
    0x08,
    0x09,
    0x0a,
    0x0b,
    0x0c,
    0x0d,
    0x0f,
    0x10,
    0x13,
    0x15,
    0x19,
    0x1f,
    0x27,
    0x34,
    0x4f,
    0x9f,
    0xff,
};
#else
#error "CPU frequency not supported."
#endif

typedef enum {
    CMD_GET_ERROR = 0x40,
    CMD_GET_BAUDRATE_PRESCALER,
    CMD_DETECT_BAUDRATE,
    CMD_SET_BAUDRATE,
    CMD_DISABLE,
    CMD_RESET,
    CMD_GET_SIGNATURE,
    CMD_SEND_BREAK,
    CMD_RECV_BREAK,
    CMD_GO,
    CMD_STEP,
    CMD_CONTINUE,
    CMD_WAIT,
    CMD_WRITE_INSTRUCTION,
    CMD_SET_PC,
    CMD_GET_PC,
    CMD_REGISTERS,
    CMD_SRAM,
    CMD_READ_FLASH,
    CMD_WRITE_FLASH_PAGE,
} usb_command_t;

typedef enum {
    ERR_NONE = 0,
    ERR_NOT_INITIALIZED,
    ERR_BAUDRATE_DETECTION,
    ERR_ECHO_MISMATCH,
    ERR_BREAK_MISMATCH,
} error_type_t;

static uint8_t buf[4];
static uint16_t ubrr = 0xffff;
static volatile error_type_t err = ERR_NOT_INITIALIZED;
static bool after_break = false;
static volatile uint16_t remaining = 0;
static volatile bool data_on = false;
static bool writing_flash_page = false;
static uint16_t flash_page_start = 0;


void
data_led_on(void)
{
    data_on = true;;
    PORTD |= (1 << 6);
}


void
data_led_off(void)
{
    if (data_on) {
        data_on = false;
        PORTD &= ~(1 << 6);
    }
}


static void
detect_baudrate(void)
{
    usart_clean();
    usart_init(0);

    for (uint8_t i = 0; ubrr_values[i] != 0xff; i++) {
        wdt_reset();
        usart_clean();
        usart_init(ubrr_values[i]);
        usart_send_break();
        if (0x55 == usart_recv_break_with_timeout(0xff)) {
            ubrr = ubrr_values[i];
            return;
        }
    }

    err = ERR_BAUDRATE_DETECTION;
    ubrr = 0xffff;
}


static void
send_byte(uint8_t b)
{
    if (err != ERR_NONE)
        return;

    usart_send_byte(b);
    uint8_t c = usart_recv_byte();
    if (b != c) {
        err = ERR_ECHO_MISMATCH;
    }
}


static void
recv_break()
{
    if (err != ERR_NONE)
        return;

    wdt_reset();
    uint8_t c = usart_recv_break();
    if (c != 0x55) {
        err = ERR_BREAK_MISMATCH;
    }
    else {
        after_break = true;
    }
}


static void
send_break()
{
    if (err != ERR_NONE)
        return;

    usart_send_break();
    recv_break();
}


static void
registers(uint8_t start, uint8_t len, bool write)
{
    if (err != ERR_NONE)
        return;

    send_byte(0x66);
    send_byte(0xd0);
    send_byte(0x00);
    send_byte(start);
    send_byte(0xd1);
    send_byte(0x00);
    send_byte(start + len);
    send_byte(0xc2);
    send_byte(write ? 0x05 : 0x01);
    send_byte(0x20);
}


static void
write_instruction(uint16_t inst)
{
    if (err != ERR_NONE)
        return;

    send_byte(0x64);
    send_byte(0xd2);
    send_byte(inst >> 8);
    send_byte(inst);
    send_byte(0x23);
}


usbMsgLen_t
usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void*) data;
    bool write = (rq->bmRequestType & USBRQ_DIR_MASK) == USBRQ_DIR_HOST_TO_DEVICE;

    switch ((usb_command_t) rq->bRequest) {

        case CMD_GET_ERROR: {
            buf[0] = err;
            usbMsgPtr = buf;
            return 1;
        }

        case CMD_GET_BAUDRATE_PRESCALER: {
            err = ERR_NONE;
            buf[0] = 16;
            buf[1] = ((float) F_CPU)/1000000;
            usbMsgPtr = buf;
            return 2;
        }

        case CMD_DETECT_BAUDRATE: {
            err = ERR_NONE;
            detect_baudrate();
            buf[0] = ubrr >> 8;
            buf[1] = ubrr;
            usbMsgPtr = buf;
            return 2;
        }

        case CMD_SET_BAUDRATE: {
            err = ERR_NONE;
            ubrr = rq->wValue.word;
            usart_clean();
            usart_init(ubrr);
            return 0;
        }

        case CMD_DISABLE: {
            err = ERR_NONE;
            send_byte(0x06);
            return 0;
        }

        case CMD_RESET: {
            err = ERR_NONE;
            send_break();
            send_byte(0x07);
            recv_break();
            return 0;
        }

        case CMD_GET_SIGNATURE: {
            err = ERR_NONE;
            send_byte(0xf3);
            buf[0] = usart_recv_byte();
            buf[1] = usart_recv_byte();
            usbMsgPtr = buf;
            return 2;
        }

        case CMD_SEND_BREAK: {
            err = ERR_NONE;
            send_break();
            return 0;
        }

        case CMD_RECV_BREAK: {
            err = ERR_NONE;
            recv_break();
            return 0;
        }

        case CMD_GO: {
            err = ERR_NONE;
            send_byte(0x40);
            send_byte(0x30);
            return 0;
        }

        case CMD_STEP: {
            err = ERR_NONE;
            send_byte(0x60);
            send_byte(0x31);
            recv_break();
            return 0;
        }

        case CMD_CONTINUE: {
            // idx: byte 0 -> hw bp set
            //      byte 1 -> timers
            err = ERR_NONE;
            uint8_t t = 0x60;
            if (rq->wIndex.word & (1 << 0)) {
                t = 0x61;
                send_byte(0xd1);
                uint8_t bp = rq->wValue.word / 2;
                send_byte(bp >> 8);
                send_byte(bp);
            }
            if (rq->wIndex.word & (1 << 1)) {
                t -= 0x20;
            }
            send_byte(t);
            send_byte(0x30);
            return 0;
        }

        case CMD_WAIT: {
            err = ERR_NONE;
            buf[0] = usart_wait() ? 0xff : 0;
            usbMsgPtr = buf;
            return 1;
        }

        case CMD_WRITE_INSTRUCTION: {
            err = ERR_NONE;
            write_instruction(rq->wValue.word);
            return 0;
        }

        case CMD_SET_PC: {
            err = ERR_NONE;
            send_byte(0xd0);
            uint8_t b = rq->wValue.word / 2;
            send_byte(b >> 8);
            send_byte(b);
            after_break = false;
            return 0;
        }

        case CMD_GET_PC: {
            err = ERR_NONE;
            send_byte(0xf0);
            uint16_t b = usart_recv_byte() << 8;
            b |= usart_recv_byte();
            if (after_break) {
                b--;
                after_break = false;
            }
            b *= 2;
            buf[0] = b >> 8;
            buf[1] = b;
            usbMsgPtr = buf;
            return 2;
        }

        case CMD_REGISTERS: {
            err = ERR_NONE;
            registers(rq->wValue.word, rq->wLength.word, write);
            remaining = rq->wLength.word;
            return USB_NO_MSG;
        }

        case CMD_SRAM: {
            err = ERR_NONE;
            registers(30, 2, true);
            send_byte(rq->wValue.word);
            send_byte(rq->wValue.word >> 8);
            uint16_t l = rq->wLength.word * 2;
            if (write) {
                l++;
            }
            send_byte(0x66);
            send_byte(0xd0);
            send_byte(0x00);
            send_byte(write ? 0x01 : 0x00);
            send_byte(0xd1);
            send_byte(l >> 8);
            send_byte(l);
            send_byte(0xc2);
            send_byte(write ? 0x04 : 0x00);
            send_byte(0x20);
            remaining = rq->wLength.word;
            return USB_NO_MSG;
        }

        case CMD_READ_FLASH: {
            err = ERR_NONE;
            registers(30, 2, true);
            send_byte(rq->wValue.word);
            send_byte(rq->wValue.word >> 8);
            uint16_t l = rq->wLength.word * 2;
            send_byte(0x66);
            send_byte(0xd0);
            send_byte(0x00);
            send_byte(0x00);
            send_byte(0xd1);
            send_byte(l >> 8);
            send_byte(l);
            send_byte(0xc2);
            send_byte(0x02);
            send_byte(0x20);
            remaining = rq->wLength.word;
            return USB_NO_MSG;
        }

        case CMD_WRITE_FLASH_PAGE: {
            err = ERR_NONE;
            registers(29, 3, true);
            send_byte(DW_CTPB | DW_SPMEN);
            send_byte(rq->wValue.word);
            send_byte(rq->wValue.word >> 8);
            write_instruction(DW_OUT_SPMCSR_29);
            write_instruction(DW_SPM);
            send_break();

            registers(29, 1, true);
            send_byte(DW_PGERS | DW_SPMEN);
            write_instruction(DW_OUT_SPMCSR_29);
            write_instruction(DW_SPM);
            send_break();

            registers(29, 1, true);
            send_byte(DW_SPMEN);

            writing_flash_page = true;
            flash_page_start = rq->wValue.word;
            remaining = rq->wLength.word;
            return USB_NO_MSG;
        }
    }

    return 0;
}


uchar
usbFunctionRead(uchar *data, uchar len)
{
    uint8_t i = 0;
    while (i < len && remaining--) {
        wdt_reset();
        data[i++] = usart_recv_byte();
    }
    return i;
}


uchar
usbFunctionWrite(uchar *data, uchar len)
{
    uint8_t i = 0;
    while (i < len && remaining) {
        wdt_reset();

        if (writing_flash_page) {
            uint8_t reg = remaining % 2;
            registers(reg, 1, true);
            send_byte(data[i++]);

            if (reg == 1) {
                write_instruction(DW_OUT_SPMCSR_29);
                write_instruction(DW_SPM);
                write_instruction(DW_ADIW_30_2);
            }

        }
        else {
            send_byte(data[i++]);
        }
        remaining--;
    }

    if (writing_flash_page && !remaining) {
        wdt_reset();
        registers(29, 3, true);
        send_byte(DW_PGWRT | DW_SPMEN);
        send_byte(flash_page_start);
        send_byte(flash_page_start >> 8);
        write_instruction(DW_OUT_SPMCSR_29);
        write_instruction(DW_SPM);
        send_break();
        writing_flash_page = false;
    }

    return remaining ? 0 : 1;
}


int
main(void)
{
    wdt_enable(WDTO_1S);

    DDRD |= (1 << 5) | (1 << 6);

    usbInit();
    usbDeviceDisconnect();

    uint8_t i = 0xff;
    while (i--) {
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();

    sei();

    for (;;) {
        wdt_reset();
        usbPoll();
        data_led_off();
    }

    return 0;
}
