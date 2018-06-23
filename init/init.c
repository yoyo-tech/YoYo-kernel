//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "../arm/uart.h"
#include "../arm/mailboxes.h"

#define UNUSED(x) ((void)(x))

void kernelInit(unsigned int r0, unsigned int r1, unsigned int atags) {
    // Kernel execution environment initialization
    UNUSED(r0);
    UNUSED(r1);
    UNUSED(atags);

    UART0init();

    UART0puts("Hello YoYo!!!!!!!!!!!!!\n");
    UART0hex(0xABCD);

    for(;;)
        ;

    /*
     * while(1) { UART0putchar(UART0_getchar());       <-- echo everything back
     */
}