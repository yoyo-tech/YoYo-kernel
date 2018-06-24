//
// Created by YoYo kernel team on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "delays.h"

/**
 * Sleep for a specific amount of cycles
 *
 * @param cycles number of cycles to sleep
 */
void sleepCycles(unsigned int cycles) {
    if(cycles != 0) {
        while(cycles--) {
            asm volatile("nop");
        }
    }
}

/**
 * Sleep for a specific amount of seconds
 *
 * @param seconds number of seconds to sleep
 */
void sleep(unsigned int seconds) {
    seconds *= 1000000;           // from seconds to microseconds

    register unsigned long f, t, r;

    // get the current counter frequency
    asm volatile("mrs %0, cntfrq_el0"
                 : "=r"(f));

    // read the current counter
    asm volatile("mrs %0, cntpct_el0"
                 : "=r"(t));

    // calculate expire value for counter
    t += (((f / 1000) * seconds)/1000);
    do {
        asm volatile("mrs %0, cntpct_el0"
                     : "=r"(r));
    } while(r < t);
}