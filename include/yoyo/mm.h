//
// Created by YoYo kernel team on 27.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_MM_H
#define YOYO_KERNEL_MM_H

#define     PAGE_SIZE       4096
#define     TTBR_ENABLE     1

/**
 * Initializes the MM kernel's subsystem
 */
void mmInit();

#endif //YOYO_KERNEL_MM_H