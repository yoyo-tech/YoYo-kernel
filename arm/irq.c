//
// Created by YoYo kernel team on 30.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "io.h"
#include "irq.h"
#include <yoyo/debug.h>

// Devices' headers from which we handle IRQs
#include "timer.h"

const char *errorMessages[] = {
        "SYNC_INVALID_EL1t",
        "IRQ_INVALID_EL1t",
        "FIQ_INVALID_EL1t",
        "ERROR_INVALID_EL1T",

        "SYNC_INVALID_EL1h",
        "IRQ_INVALID_EL1h",     // the most important
        "FIQ_INVALID_EL1h",
        "ERROR_INVALID_EL1h",

        "SYNC_INVALID_EL0_64",
        "IRQ_INVALID_EL0_64",
        "FIQ_INVALID_EL0_64",
        "ERROR_INVALID_EL0_64",

        "SYNC_INVALID_EL0_32",
        "IRQ_INVALID_EL0_32",
        "FIQ_INVALID_EL0_32",
        "ERROR_INVALID_EL0_32"
};

/**
 * Enables currently handled by YoYo IRQs at interrupt controller.
 */
void enableInterruptController() {
    // currently only timer
    out32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}

/**
 * Handles all types of exceptions expect IRQs from EL1.
 *
 * @param type
 * @param esr
 * @param address address of instruction that generated an exception
 */
void showInvalidEntryMessage(int type, unsigned long esr, unsigned long address) {
    char buffer[100];

    snprintf(buffer, 100, "%s, ESR: %x, address: %x\n", errorMessages[type], esr, address);
    printDebug(buffer);
}

/**
 * Handles standard IRQ EL1.
 */
void handleIRQ() {
    printDebug("asdsadsa");

    unsigned int IRQ = in32(IRQ_PENDING_1);     // number of pending IRQ from first interrupt controller
            // interrupts 0 - 31

    char buffer[100];
    // currently supports IRQ
    switch(IRQ) {
        case SYSTEM_TIMER_IRQ_1:
            printDebug("timer interrupt!\n");
            timerIRQHandler();
            break;
        default:
            snprintf(buffer, 100, "Unknown pending IRQ: %x\n", IRQ);
            printDebug(buffer);
            break;
    }
}