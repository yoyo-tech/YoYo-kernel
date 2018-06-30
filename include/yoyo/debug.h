//
// Created by YoYo kernel team on 26.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_DEBUG_H
#define YOYO_KERNEL_DEBUG_H

#include <stdarg.h>

#define SPACES_PER_TAB 4

/**
 * Prints string.
 *
 * @param s string to print
 */
void printDebug(const char *s);

int vsnprintf(char* buffer, unsigned int len, const char *fmt, va_list va);
int snprintf(char* buffer, unsigned int len, const char *fmt, ...);

#endif //YOYO_KERNEL_DEBUG_H
