//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

// UART0 interface, used for displaying debugging messages
// Don't use UART1(we don't even initialize it) because qemu don't want to redirect UART1 IO to standard terminal's IO

#include "gpio.h"
#include "mailboxes.h"
#include "uart.h"

// UART0 registers
#define UART0_DR        ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201000))
#define UART0_FR        ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201018))
#define UART0_IBRD      ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201024))
#define UART0_FBRD      ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201028))
#define UART0_LCRH      ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x0020102C))
#define UART0_CR        ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201030))
#define UART0_IMSC      ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201038))
#define UART0_ICR       ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00201044))

static inline void delay(unsigned int cpuCycles) {
    while(cpuCycles != 0) {
        asm volatile("nop");
        cpuCycles--;
    }
}

static inline void UART0BufferWait(unsigned int bitMask) {
    do {
        asm volatile("nop");
    } while(*UART0_FR & bitMask);
}

/**
 * Initialization of UART0.
 */
void UART0init() {
    register unsigned int r;

    // Initialize UART0
    *UART0_CR = 0;          // turn off UART0

    // Set up clock for consistent divisor values!
    mailbox[0] = 8*4;
    mailbox[1] = MAILBOX_REQUEST;
    mailbox[2] = MAILBOX_TAG_SETCLOCKRATE; // set clock rate
    mailbox[3] = 12;
    mailbox[4] = 8;
    mailbox[5] = 2;           // UART0 clock
    mailbox[6] = 4000000;     // 4Mhz
    mailbox[7] = MAILBOX_TAG_LAST;
    mailboxCall(MAILBOX_PROP);

    /* map UART0 to GPIO pins */
    r = *GPFSEL1;
    r &= (~( (7 << 12) | (7 << 15) ));  // gpio14, gpio15
    r |= ((4 << 12) | (4 << 15));       // alt0
    *GPFSEL1 = r;
    *GPPUD = 0;            // enable pins 14 and 15
    delay(150);

    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    delay(150);

    *GPPUDCLK0 = 0;        // flush GPIO setup

    *UART0_ICR = 0x7FF;    // clear interrupts
    *UART0_IBRD = 2;       // 115200 baud
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0b11<<5; // 8n1
    *UART0_CR = 0x301; // enable Tx, Rx, FIFO
}

/**
 * Sends character to UART0.
 *
 * @param ch character to send
 */
void UART0putchar(unsigned int ch) {
    // Wait until we can send
    UART0BufferWait(0x20);

    // Write the character to the buffer
    *UART0_DR = ch;
}

/**
 * Receives character from UART0.
 *
 * @return received character
 */
char UART0getchar() {
    char ch;

    // Wait until something is in the buffer
    UART0BufferWait(0x10);

    // Read character and return
    ch = (char)(*UART0_DR);

    // Convert \r to \n if new line character.
    if(ch == '\r') {
        ch = '\n';
    }

    return ch;
}

/**
 * Prints a string on UART0.
 *
 * @param s string to print
 */
void UART0puts(const char *s) {
    while(*s) {
        // Convert \n to UART0's \r
        if(*s == '\n') {
            UART0putchar('\r');
        }

        UART0putchar(*s);
        s++;
    }
}

/**
 * Prints a number in hex format.
 *
 * @param ch number to print
 */
void UART0hex(unsigned int number) {
    char outbuf[16];     // max 16 digits (without 0x)

    UART0puts("0x");
    int i = 12;
    int j = 0;

    do {
        outbuf[i] = "0123456789ABCDEF"[number % 16];
        i--;
        number /= 16;
    } while(number > 0);

    while(++i < 13){
        outbuf[j++] = outbuf[i];
    }

    outbuf[j] = 0;

    UART0puts(outbuf);
}