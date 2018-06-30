//
// Created by YoYo kernel team on 30.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_TIMER_H
#define YOYO_KERNEL_TIMER_H

#include "gpio.h"

// Timer registers
#define TIMER_CS        (MMIO_BASE_ADDRESS+0x00003000)
#define TIMER_CLO       (MMIO_BASE_ADDRESS+0x00003004)
#define TIMER_CHI       (MMIO_BASE_ADDRESS+0x00003008)
#define TIMER_C0        (MMIO_BASE_ADDRESS+0x0000300C)
#define TIMER_C1        (MMIO_BASE_ADDRESS+0x00003010)
#define TIMER_C2        (MMIO_BASE_ADDRESS+0x00003014)
#define TIMER_C3        (MMIO_BASE_ADDRESS+0x00003018)

#define TIMER_CS_M0	    (1 << 0)
#define TIMER_CS_M1	    (1 << 1)
#define TIMER_CS_M2	    (1 << 2)
#define TIMER_CS_M3	    (1 << 3)

/**
 * Initializes the timer.
 */
void timerInit();

/**
 * Timer's IRQ handler.
 */
void timerIRQHandler();

#endif //YOYO_KERNEL_TIMER_H
