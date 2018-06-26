//
// Created by YoYo kernel team on 26.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#ifndef YOYO_KERNEL_PSF_H
#define YOYO_KERNEL_PSF_H

// PSF header format
typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int headerSize;
    unsigned int flags;
    unsigned int numGlyph;
    unsigned int bytesPerGlyph;
    unsigned int height;
    unsigned int width;
    unsigned char glyphs;
} __attribute__((packed)) PSF;

// address of start PSF font - name of this external ELF symbol is dependant of font localization and name!!!!!!!!
// _binary_path_start
extern volatile unsigned char _binary_init_bootFonts_mainFont_psf_start;

#endif //YOYO_KERNEL_PSF_H
