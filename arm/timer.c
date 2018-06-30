//
// Created by YoYo kernel team on 30.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "timer.h"
#include "io.h"
#include <yoyo/debug.h>

const unsigned int interval = 200;

// Main timing variable
unsigned int timingVariable = 0;

/**
 * Initializes the timer.
 */
void timerInit() {
    timingVariable = in32(TIMER_CLO);
    timingVariable += interval;

    out32(TIMER_C1, timingVariable);
}

/**
 * Timer's IRQ handler.
 */
void timerIRQHandler() {
    timingVariable += interval;

    out32(TIMER_C1, timingVariable);
    out32(TIMER_CS, TIMER_CS_M1);

    printDebug("Timer interrupt received!\n");
}
