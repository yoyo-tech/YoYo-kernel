//
// Created by YoYo kernel team on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_DELAYS_H
#define YOYO_KERNEL_DELAYS_H

/**
 * Sleep for a specific amount of cycles
 *
 * @param cycles number of cycles to sleep
 */
void sleepCycles(unsigned int cycles);

/**
 * Sleep for a specific amount of seconds
 *
 * @param seconds number of seconds to sleep
 */
void sleep(unsigned int seconds);

#endif //YOYO_KERNEL_DELAYS_H
