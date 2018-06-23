//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

// API for comfortable usage of mailboxes - communication with the firmware

#include "mailboxes.h"
#include "gpio.h"

// properly aligned buffer that represents messages sent and received from mailboxes
                            // 16 bytes address alignment
volatile unsigned int __attribute__((aligned(16))) mailbox[36];

// Memory addresses used to provide communication with mailboxes
#define MAILBOX_VIDEOCORE       (MMIO_BASE_ADDRESS+0x0000B880)
#define MAILBOX_READ            ((volatile unsigned int*)(MAILBOX_VIDEOCORE+0x0))
#define MAILBOX_POLL            ((volatile unsigned int*)(MAILBOX_VIDEOCORE+0x10))
#define MAILBOX_SENDER          ((volatile unsigned int*)(MAILBOX_VIDEOCORE+0x14))
#define MAILBOX_STATUS          ((volatile unsigned int*)(MAILBOX_VIDEOCORE+0x18))
#define MAILBOX_CONFIG          ((volatile unsigned int*)(MAILBOX_VIDEOCORE+0x1C))
#define MAILBOX_WRITE           ((volatile unsigned int*)(MAILBOX_VIDEOCORE+0x20))
#define MAILBOX_RESPONSE        0x80000000
#define MAILBOX_FULL            0x80000000
#define MAILBOX_EMPTY           0x40000000

static inline void mailboxWait(unsigned long waitCondition) {
    do {
        asm volatile("nop");
    } while(*MAILBOX_STATUS & waitCondition);
}

/**
 * Makes call to mailbox.
 * Before call you must zero and fill(refill) mailbox array.
 *
 * @param channel - destination mailbox channel
 * @return ReturnStatus
 */
ReturnStatus mailboxCall(unsigned char channel) {
    unsigned int readValue;
    ReturnStatus returnStatus;

    // Wait until we can write to the mailbox
    mailboxWait(MAILBOX_FULL);

    // Write the address of our message to the mailbox with channel identifier
    *MAILBOX_WRITE = (((unsigned int)((unsigned long)&mailbox)&~0xF) | (channel & 0xF));

    // Wait for response
    while(1) {
        // Is there a response?
        mailboxWait(MAILBOX_EMPTY);

        readValue = *MAILBOX_READ;

        // Is it a response to our message?
        if((unsigned char)(readValue & 0xF) == channel
           && (readValue & ~0xF) == (unsigned int)((unsigned long)&mailbox)) {
            // Is it a valid successful response?
            if(mailbox[1] == MAILBOX_RESPONSE) {
                returnStatus.exitCode = 0;
                returnStatus.status = SUCCESS;
            } else {
                returnStatus.exitCode = 1;
                returnStatus.status = FAILURE;
            }

            return returnStatus;
        }
    }
}