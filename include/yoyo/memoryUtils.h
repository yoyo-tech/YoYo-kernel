//
// Created by YoYo kernel team on 25.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_MEMORYUTILS_H
#define YOYO_KERNEL_MEMORYUTILS_H

#include <yoyo/types.h>

/**
 * Copy a block of memory, handling overlap.
 *
 * @param dest destination
 * @param src source
 * @param n bytes count
 * @return pointer to a destination
 */
void *memcpy(void *dest, const void *src, size_t n);

/**
 * Moves blocks of memory.
 *
 * @param dest destination
 * @param src source
 * @param n bytes count
 * @return pointer to a destination
 */
void *memmove(void *dest, const void *src, size_t n);

/**
 * Sets the area of memory with received value.
 *
 * @param src pointer to start of memory area
 * @param x values at which memory will be set
 * @param n bytes count
 * @return pointer to a destination
 */
void *memset(void *dest, int x, size_t n);

/**
 * Zeroes the next byte which starts at dest.
 *
 * @param dest area of memory where the byte starts
 */
void bzero(void *dest);

#endif //YOYO_KERNEL_MEMORYUTILS_H
