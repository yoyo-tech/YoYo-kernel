//
// Created by YoYo kernel team on 30.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_IO_H
#define YOYO_KERNEL_IO_H

/**
 * Sends 32-bit data to address.
 *
 * @param address
 * @param data
 */
extern void out32(unsigned long address, unsigned int data);

/**
 * Gets 32-bit data from address.
 *
 * @param address
 * @return 32-bit data from address
 */
extern unsigned int in32(unsigned long address);

#endif //YOYO_KERNEL_IO_H
