//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include <yoyo/arm.h>

// ARM IS LITTLE-ENDIAN, SO ABGR
int rgba(int r, int g, int b, int a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

// unsigned int r0, unsigned int r1, unsigned int atags
void kernelInit() {
    // Kernel execution environment initialization
//    UNUSED(r0);
//    UNUSED(r1);
//    UNUSED(atags);

    UART0init();
    randInit();
    framebufferInit();

    UART0puts("Hello YoYo!!!!!!!!!!!!!\n");

    UART0puts("Width: ");
    UART0hex(screenWidth);
    UART0putchar('\n');

    UART0puts("Height: ");
    UART0hex(screenHeight);
    UART0putchar('\n');

    UART0puts("Pitch: ");
    UART0hex(screenPitch);
    UART0putchar('\n');

    UART0hex(framebuffer == 0);

//    sleep(6);
//    UART0hex(0xABCD);
//
//    sleepCycles(30000);
//    UART0putchar('\n');
//    UART0hex(rand(1, 10));

    // red background
    unsigned char *vram = (unsigned char *) framebuffer;
    for(int i = 0; i < screenWidth;i++) {
        for(int j = 0; j < screenHeight;j++) {
            *((unsigned int *)vram) = rgba(0, 0xFF, 0, 0);
            vram += 4;      // 4 bytes forward
        }
    }

    //powerOFFMachine();

    for(;;)
        ;

    /*
     * while(1) { UART0putchar(UART0_getchar());       <-- echo everything back
     */
}