//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include <yoyo/arm.h>
#include <yoyo/debug.h>
#include <yoyo/mm.h>
#include <stdarg.h>

// ARM IS LITTLE-ENDIAN, SO ABGR
int rgba(int r, int g, int b, int a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

extern volatile unsigned char _end;    // end of physical our memory

#define MESSAGE_BUFFER_LENGTH 100
static char messageBuffer[MESSAGE_BUFFER_LENGTH];
static void zeroMessageBuffer() {
    for(int i = 0; i < MESSAGE_BUFFER_LENGTH;i++) {
        messageBuffer[i] = 0;
    }
}

static void INITPrintf(const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vsnprintf(messageBuffer, MESSAGE_BUFFER_LENGTH, fmt, va);
    va_end(va);

    printDebug(messageBuffer);
    UART0puts(messageBuffer);

    zeroMessageBuffer();
}

// unsigned int r0, unsigned int r1, unsigned int atags
void kernelInit() {
    zeroMessageBuffer();
    UART0init();
    UART0puts("\nStarting ARM PC...\n");

    randInit();
    framebufferInit();

    INITPrintf("Initializing YoYo...\n");
    INITPrintf("Random generator subsystem initialized!\n");
    INITPrintf("Framebuffer HDMI's initialized!\n");
    INITPrintf("Width: %d\n", screenWidth);
    INITPrintf("Height: %d\n", screenHeight);
    INITPrintf("Pitch: %d\n", screenPitch);
    INITPrintf("Current execution level: %d\n", getExecutionLevel());

    mmInit();
    INITPrintf("Memory management subsystem initialized!\n");

    for(;;)
        ;

//#define KERNEL_UART0_DR        ((volatile unsigned int*)0xFFFFFFFFFFE00000)
//#define KERNEL_UART0_FR        ((volatile unsigned int*)0xFFFFFFFFFFE00018)
//
//    char *x = "MMU MAPPED";
//    // test mapping
//    while(*x) {
//        /* wait until we can send */
//        do{asm volatile("nop");}while(*KERNEL_UART0_FR&0x20);
//        /* write the character to the buffer */
//        *KERNEL_UART0_DR=*x++;
//    }
}