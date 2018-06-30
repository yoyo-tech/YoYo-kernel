//
// Created by YoYo kernel team on 29.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

.globl getExecutionLevel
getExecutionLevel:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret
