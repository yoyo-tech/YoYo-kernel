//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include <yoyo/arm.h>
#include <yoyo/debug.h>

// ARM IS LITTLE-ENDIAN, SO ABGR
int rgba(int r, int g, int b, int a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

void makeBackground(int rgba) {
    unsigned char *vram = (unsigned char *) framebuffer;
    for(int i = 0; i < screenWidth;i++) {
        for(int j = 0; j < screenHeight;j++) {
            *((unsigned int *)vram) = rgba;
            vram += 4;      // 4 bytes forward
        }
    }
}

#include "homerImage.h"

void showPicture() {
    // shows hornerImage.h
    int x, y;
    unsigned char *vram = (unsigned char *) framebuffer;
    char *data = homer_data, pixel[4];

    vram += (screenHeight - homer_height) / 2 * screenPitch + (screenWidth - homer_width)*2;
    for(y = 0; y < homer_height;y++) {
        for(x = 0; x < homer_width;x++) {
            HEADER_PIXEL(data, pixel);

            *((unsigned int *)vram) = *((unsigned int *)&pixel);
            vram += 4;
        }
        vram += screenPitch - homer_width*4;
    }
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

    printDebug("helloooooooooooo\noooo\t\tooooooo\noo");
    printDebug("\n\n\n\n\n");
    printDebug("woooooooooooot\tXD");

    for(;;)
        ;
}