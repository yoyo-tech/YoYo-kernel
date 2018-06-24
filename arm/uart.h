//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_UART_H
#define YOYO_KERNEL_UART_H

// UART0 interface, used for displaying debugging messages
// Don't use UART1(we don't even initialize it) because qemu don't want to redirect UART1 IO to standard terminal's IO

/**
 * Initialization of UART0.
 */
void UART0init();

/**
 * Sends character to UART0.
 *
 * @param ch character to send
 */
void UART0putchar(unsigned int ch);

/**
 * Receives character from UART0.
 *
 * @return received character
 */
char UART0getchar();

/**
 * Prints a string on UART0.
 *
 * @param s string to print
 */
void UART0puts(const char *s);

/**
 * Prints a number in hex format.
 *
 * @param ch number to print
 */
void UART0hex(unsigned int number);

#endif //YOYO_KERNEL_UART_H
