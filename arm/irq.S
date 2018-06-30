//
// Created by YoYo kernel team on 30.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

/* ON IRQ */
.globl enableInterrupts
enableInterrupts:
    msr    daifclr, #2
    ret

/* OFF IRQ */
.globl disableInterrupts
disableInterrupts:
    msr    daifset, #2
    ret