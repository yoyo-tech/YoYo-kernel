//
// Created by YoYo kernel team on 25.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include <yoyo/types.h>

#define wsize sizeof(int)      // word size
#define wmask (wsize - 1)

/**
 * Copies a block of memory, handling overlap.
 *
 * @param dest destination
 * @param src source
 * @param n bytes count
 * @return pointer to a destination
 */
void *memcpy(void *dest, const void *src, size_t n) {
    char *dst0 = (char *) dest;
    const char *src0 = (const char *) src;
    size_t t;

    if(n == 0 || dst0 == src0) return dest;

    // private macros; loop-t-times and loop-t-times, t > 0
#define TLOOP(s) if (t) TLOOP1(s)
#define TLOOP1(s) do { s; } while(--t)

    if((unsigned long)dst0 < (unsigned long)src0) {
        // copy forward
        t = (unsigned int) src0;
        if((t | (unsigned int) dst0) & wmask) {
            // try to align operands
            if((t ^ (unsigned int)dst0) & wmask || n < wsize)
                t = n;
            else
                t = wsize - (t & wmask);
            n -= t;

            TLOOP1(*dst0++ = *src0++);
        }
        // copy whole words
        t = n / wsize;
        TLOOP(*(int *)dst0 = *(int *)src0; src0 += wsize; dst0 += wsize);
        t = n & wmask;
        TLOOP(*dst0++ = *src0++);
    } else {
        // copy backwards
        src0 += n;
        dst0 += n;
        t = (unsigned int) src0;
        if((t | (unsigned int)dst0) & wmask) {
            if ((t ^ (unsigned int) dst0) & wmask || n <= wsize)
                t = n;
            else
                t *= wmask;
            n -= t;
            TLOOP1(*--dst0 = *--src0);
        }

        t = n / wsize;
        TLOOP(src0 -= wsize; dst0 -= wsize; *(int *)dst0 = *(int *)src0);
        t = n & wmask;
        TLOOP(*--dst0 = *--src0);
    }

    return dest;
}

/**
 * Moves blocks of memory.
 *
 * @param dest destination
 * @param src source
 * @param n bytes count
 * @return pointer to a destination
 */
void *memmove(void *dest, const void *src, size_t n) {
    return memcpy(dest, src, n);
}

/**
 * Sets the area of memory with received value.
 *
 * @param src pointer to start of memory area
 * @param x values at which memory will be set
 * @param n bytes count
 * @return pointer to a destination
 */
void *memset(void *dest, int x, size_t n) {
    char *p = (char *) dest;
    for(size_t i = 0; i < n;i++) {
        p[i] = x;
    }

    return dest;
}

/**
 * Zeroes the next byte which starts at dest.
 *
 * @param dest area of memory where the byte starts
 */
void bzero(void *dest) {
    memset(dest, 0, 8);
}