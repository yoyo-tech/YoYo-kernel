//
// Created by YoYo kernel team on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "gpio.h"

#define RNG_CTRL        ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00104000))
#define RNG_STATUS      ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00104004))
#define RNG_DATA        ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00104008))
#define RNG_INT_MASK    ((volatile unsigned int*)(MMIO_BASE_ADDRESS+0x00104010))

/**
 * Initializes random number hardware generator.
 */
void randInit() {
    *RNG_STATUS=0x40000;

    // mask interrupt
    *RNG_INT_MASK|=1;

    // enable
    *RNG_CTRL|=1;

    // wait for gaining some entropy
    while(!((*RNG_STATUS)>>24)) asm volatile("nop");
}

/**
 * Returns random number based on arguments.
 *
 * @param min starting range for random number(>= 0)
 * @param max ending range for random number(>= 0)
 * @return random number(>= 0)
 */
unsigned int rand(unsigned int min, unsigned int max) {
    return (*RNG_DATA % (max - min) + min);
}