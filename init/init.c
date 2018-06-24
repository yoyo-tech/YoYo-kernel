//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include <yoyo/arm.h>

// unsigned int r0, unsigned int r1, unsigned int atags
void kernelInit() {
    // Kernel execution environment initialization
//    UNUSED(r0);
//    UNUSED(r1);
//    UNUSED(atags);

    UART0init();
    randInit();

    UART0puts("Hello YoYo!!!!!!!!!!!!!\n");
    sleep(6);
    UART0hex(0xABCD);

    sleepCycles(30000);
    UART0putchar('\n');
    UART0hex(rand(1, 10));

    for(;;)
        ;

    /*
     * while(1) { UART0putchar(UART0_getchar());       <-- echo everything back
     */
}