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
    UART0init();
    UART0puts("Initializing YoYo...\n");

    randInit();
    framebufferInit();

    UART0puts("Width: "); UART0hex(screenWidth); UART0putchar('\n');

    UART0puts("Height: "); UART0hex(screenHeight); UART0putchar('\n');

    UART0puts("Pitch: "); UART0hex(screenPitch); UART0putchar('\n');

    // red background
//    unsigned char *vram = (unsigned char *) framebuffer;
//    for(int i = 0; i < screenWidth;i++) {
//        for(int j = 0; j < screenHeight;j++) {
//            *((unsigned int *)vram) = rgba(0, 0xFF, 0, 0);
//            vram += 4;      // 4 bytes forward
//        }
//    }



    for(;;)
        ;
}