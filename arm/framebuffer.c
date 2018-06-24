//
// Created by YoYo kernel team on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "uart.h"
#include "mailboxes.h"

/**
 * Main framebuffer, you can cast it to other types as you want.
 */
void *framebuffer;

/**
 * Width of real screen.
 */
int screenWidth;

/**
 * Height of real screen.
 */
int screenHeight;

/**
 * Pitch of real screen(distance between pixels).
 */
int screenPitch;

/**
 * Initialization of framebuffer subsystem and the framebuffer pointer.
 */
void framebufferInit() {
    mailbox[0] = 35*4;
    mailbox[1] = MAILBOX_REQUEST;

    mailbox[2] = 0x48003;
    mailbox[3] = 8;
    mailbox[4] = 8;
    mailbox[5] = 1920;               //width
    mailbox[6] = 1080;               // height

    mailbox[7] = 0x48004;
    mailbox[8] = 8;
    mailbox[9] = 8;
    mailbox[10] = 1920;         // virtual width
    mailbox[11] = 1080;         // virtual height

    mailbox[12] = 0x48009;
    mailbox[13] = 8;
    mailbox[14] = 8;
    mailbox[15] = 0;           // x offset
    mailbox[16] = 0;           // y offset

    mailbox[17] = 0x48005;
    mailbox[18] = 4;
    mailbox[19] = 4;
    mailbox[20] = 32;          // depth - bits per pixel

    mailbox[21] = 0x48006;
    mailbox[22] = 4;
    mailbox[23] = 4;
    mailbox[24] = 1;           // RGB, not BGR preferably

    mailbox[25] = 0x40001; // get framebuffer, gets alignment on request
    mailbox[26] = 8;
    mailbox[27] = 8;
    mailbox[28] = 4096;        // framebuffer's pointer
    mailbox[29] = 0;           // size

    mailbox[30] = 0x40008; // get pitch
    mailbox[31] = 4;
    mailbox[32] = 4;
    mailbox[33] = 0;           // pitch

    mailbox[34] = MAILBOX_TAG_LAST;

    if(mailboxCall(MAILBOX_PROP).status == SUCCESS && mailbox[20] == 32 && mailbox[28] != 0) {
        mailbox[28] &= 0x3FFFFFFF;

        screenWidth = mailbox[5];
        screenHeight = mailbox[6];
        screenPitch = mailbox[33];

        framebuffer = (void*) ((unsigned long) mailbox[28]);
    } else {
        UART0puts("Unable to set screen resolution to 1920x1080x32\n");
    }
}
