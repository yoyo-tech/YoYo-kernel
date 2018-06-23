//
// Created by gjm, XVoir, Adikk on 23.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_STATUS_H
#define YOYO_KERNEL_STATUS_H

/**
 * Internal Status enum
 */
enum Status {
    SUCCESS,
    FAILURE
};

/**
 * Universal structure in YoYo's kernel that represents returned status from function.
 * Only for functions returning status, instead of "normal" value.
 * We created this to prevent constant returning int, and 0/-1 convention, because not always if function returns int it means 0/-1 status.
 */
typedef struct {
    int         exitCode;
    enum Status status;
    void        *payload;   // optional to fill as caller, but in some situations may be needed
                            // anyway we prefer to put this field now, to prevent some fucking bad situations when it comes to backward compatibility
} ReturnStatus;

#endif //YOYO_KERNEL_STATUS_H
