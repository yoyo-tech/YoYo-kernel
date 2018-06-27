//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include <yoyo/arm.h>
#include <yoyo/debug.h>
#include <yoyo/mm.h>

// ARM IS LITTLE-ENDIAN, SO ABGR
int rgba(int r, int g, int b, int a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

//void makeBackground(int rgba) {
//    unsigned char *vram = (unsigned char *) framebuffer;
//    for(int i = 0; i < screenWidth;i++) {
//        for(int j = 0; j < screenHeight;j++) {
//            *((unsigned int *)vram) = rgba;
//            vram += 4;      // 4 bytes forward
//        }
//    }
//}
//
//#include "homerImage.h"
//
//void showPicture() {
//    // shows hornerImage.h
//    int x, y;
//    unsigned char *vram = (unsigned char *) framebuffer;
//    char *data = homer_data, pixel[4];
//
//    vram += (screenHeight - homer_height) / 2 * screenPitch + (screenWidth - homer_width)*2;
//    for(y = 0; y < homer_height;y++) {
//        for(x = 0; x < homer_width;x++) {
//            HEADER_PIXEL(data, pixel);
//
//            *((unsigned int *)vram) = *((unsigned int *)&pixel);
//            vram += 4;
//        }
//        vram += screenPitch - homer_width*4;
//    }
//}

void printHex(int hex) {
    char outbuf[16];     // max 16 digits (without 0x)

    printDebug("0x");
    int i = 12;
    int j = 0;

    do {
        outbuf[i] = "0123456789ABCDEF"[hex % 16];
        i--;
        hex /= 16;
    } while(hex > 0);

    while(++i < 13){
        outbuf[j++] = outbuf[i];
    }

    outbuf[j] = 0;

    printDebug(outbuf);
}

extern volatile unsigned char _end;    // end of physical our memory

#define KERNEL_UART0_DR        ((volatile unsigned int*)0xFFFFFFFFFFE00000)
#define KERNEL_UART0_FR        ((volatile unsigned int*)0xFFFFFFFFFFE00018)

// unsigned int r0, unsigned int r1, unsigned int atags
void kernelInit() {
    UART0init();
    UART0puts("\nInitializing YoYo...\n");

    randInit();
    framebufferInit();
    UART0puts("Width: "); UART0hex(screenWidth); UART0putchar('\n');
    UART0puts("Height: "); UART0hex(screenHeight); UART0putchar('\n');
    UART0puts("Pitch: "); UART0hex(screenPitch); UART0putchar('\n');

    printDebug("Initializing YoYo...\n");
    printDebug("Random generator subsystem initialized!\n");
    printDebug("Framebuffer HDMI's initialized!\n");
    printDebug("Width: "); printHex(screenWidth); printDebug("\n");
    printDebug("Height: "); printHex(screenHeight); printDebug("\n");
    printDebug("Pitch: "); printHex(screenPitch); printDebug("\n");

    mmInit();
    printDebug("Memory management subsystem initialized!\n");

//    char *x = "MMU MAPPED";
//    // test mapping
//    while(*x) {
//        /* wait until we can send */
//        do{asm volatile("nop");}while(*KERNEL_UART0_FR&0x20);
//        /* write the character to the buffer */
//        *KERNEL_UART0_DR=*x++;
//    }

    for(;;)
        ;
}