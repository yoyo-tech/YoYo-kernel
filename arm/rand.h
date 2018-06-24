//
// Created by gjm, XVoir, Adikk on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_RAND_H
#define YOYO_KERNEL_RAND_H

/**
 * Initializes random number hardware generator.
 */
void randInit();

/**
 * Returns random number based on arguments.
 *
 * @param min starting range for random number(>= 0)
 * @param max ending range for random number(>= 0)
 * @return random number(>= 0)
 */
unsigned int rand(unsigned int min, unsigned int max);

#endif //YOYO_KERNEL_RAND_H
