//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_MAILBOXES_H
#define YOYO_KERNEL_MAILBOXES_H

// API for comfortable usage of mailboxes - communication with the firmware

#include <yoyo/status.h>

// properly aligned buffer that represents messages sent and received from mailboxes
extern volatile unsigned int mailbox[36];

#define MAILBOX_REQUEST             0

// mailboxs' channels
#define MAILBOX_POWER               0
#define MAILBOX_FB                  1
#define MAILBOX_VUART               2
#define MAILBOX_VCHIQ               3
#define MAILBOX_LEDS                4
#define MAILBOX_BTNS                5
#define MAILBOX_TOUCH               6
#define MAILBOX_COUNT               7
#define MAILBOX_PROP                8

// mailboxs' tags
#define MAILBOX_TAG_GETSERIAL       0x10004
#define MAILBOX_TAG_SETPOWER        0x28001
#define MAILBOX_TAG_SETCLOCKRATE    0x38002
#define MAILBOX_TAG_LAST            0

ReturnStatus mailboxCall(unsigned char ch);

#endif //YOYO_KERNEL_MAILBOXES_H
