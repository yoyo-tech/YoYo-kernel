//
// Created by YoYo kernel team on 24.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_FRAMEBUFFER_H
#define YOYO_KERNEL_FRAMEBUFFER_H

/**
 * Main framebuffer, you can cast it to other types as you want.
 */
extern void *framebuffer;

/**
 * Width of real screen.
 */
extern int screenWidth;

/**
 * Height of real screen.
 */
extern int screenHeight;

/**
 * Pitch of real screen(distance between pixels).
 */
extern int screenPitch;

/**
 * Initialization of framebuffer subsystem and the framebuffer pointer.
 */
void framebufferInit();

#endif //YOYO_KERNEL_FRAMEBUFFER_H
