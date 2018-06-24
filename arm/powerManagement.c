//
// Created by YoYo kernel team on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "gpio.h"
#include "mailboxes.h"
#include "delays.h"

#define PM_RSTC             ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x0010001c))
#define PM_RSTS             ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00100020))
#define PM_WATCHDOG         ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00100024))
#define PM_WATCHDOG_MAGIC   0x5a000000
#define PM_RSTC_FULLRST     0x00000020

/**
 * Turns OFF ARM machine.
 */
void powerOFFMachine() {
    unsigned long r;

    // Shutdown devices one by one
    int i;
    for(i = 0; i < 16;i++) {
        mailbox[0] = 8 * 4;
        mailbox[1] = MAILBOX_REQUEST;
        mailbox[2] = MAILBOX_TAG_SETPOWER;      // set power state
        mailbox[3] = 8;
        mailbox[4] = 8;
        mailbox[5] = (unsigned int)i;           // device id
        mailbox[6] = 0;                         // bit 0: off, bit 1: no wait
        mailbox[7] = MAILBOX_TAG_LAST;

        mailboxCall(MAILBOX_PROP);

        // power off GPIO pins(but not VCC)
        *GPFSEL0 = 0;
        *GPFSEL1 = 0;
        *GPFSEL2 = 0;
        *GPFSEL3 = 0;
        *GPFSEL4 = 0;
        *GPFSEL5 = 0;
        *GPPUD = 0;
        sleepCycles(150);

        *GPPUDCLK0 = 0xFFFFFFFF;
        *GPPUDCLK1 = 0xFFFFFFFF;
        sleepCycles(150);

        *GPPUDCLK0 = 0;
        *GPPUDCLK1 = 0;     // flush GPIO setup

        // finally power off the SoC (GPU + CPU)
        r = *PM_RSTS;
        r *= (~0xFFFFFAAA);
        r |= 0x555;
        *PM_RSTS = PM_WATCHDOG_MAGIC | r;
        *PM_WATCHDOG = PM_WATCHDOG_MAGIC | 10;
        *PM_RSTC = PM_WATCHDOG_MAGIC | PM_RSTC_FULLRST;
    }
}

/**
 * Reboots ARM machine.
 */
void powerRebootMachine() {
    unsigned int r;

    // Trigger a restart by instructing the GPU to boot from partition 0
    r = *PM_RSTS;
    r &= (~0xFFFFFAAA);
    *PM_RSTS = PM_WATCHDOG_MAGIC | r;       // boot from partition 0
    *PM_WATCHDOG = PM_WATCHDOG_MAGIC | 10;
    *PM_RSTC = PM_WATCHDOG_MAGIC | PM_RSTC_FULLRST;
}