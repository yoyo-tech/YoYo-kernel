//
// Created by YoYo kernel team on 30.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_IRQ_H
#define YOYO_KERNEL_IRQ_H

#include "gpio.h"

#define IRQ_BASIC_PENDING	(MMIO_BASE_ADDRESS+0x0000B200)
#define IRQ_PENDING_1		(MMIO_BASE_ADDRESS+0x0000B204)
#define IRQ_PENDING_2		(MMIO_BASE_ADDRESS+0x0000B208)
#define FIQ_CONTROL		    (MMIO_BASE_ADDRESS+0x0000B20C)
#define ENABLE_IRQS_1		(MMIO_BASE_ADDRESS+0x0000B210)
#define ENABLE_IRQS_2		(MMIO_BASE_ADDRESS+0x0000B214)
#define ENABLE_BASIC_IRQS	(MMIO_BASE_ADDRESS+0x0000B218)
#define DISABLE_IRQS_1		(MMIO_BASE_ADDRESS+0x0000B21C)
#define DISABLE_IRQS_2		(MMIO_BASE_ADDRESS+0x0000B220)
#define DISABLE_BASIC_IRQS	(MMIO_BASE_ADDRESS+0x0000B224)

// timer IRQs
#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)

/**
 * Enables IRQs.
 * Implemented in irq.S.
 */
extern void enableInterrupts();

/**
 * Disables IRQs.
 * Implemented in irq.S.
 */
extern void disableInterrupts();

/**
 * Enables currently handled by YoYo IRQs at interrupt controller.
 */
void enableInterruptController();

#endif //YOYO_KERNEL_IRQ_H
