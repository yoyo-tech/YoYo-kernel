//
// Created by YoYo kernel team on 26.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "../init/bootFonts/psf.h"
#include <yoyo/arm.h>

static int x = 0;
static int y = 0;

static const int SPACES_PER_TAB = 4;

/**
 * Prints string.
 *
 * @param s string to print
 */
void printDebug(const char *s) {

    // get our font
    PSF *font = (PSF *) &_binary_init_bootFonts_mainFont_psf_start;

    // draw next character if it's not zero
    while(*s) {
        // get the offset of the glyph
        unsigned char *glyph = (unsigned char *) &_binary_init_bootFonts_mainFont_psf_start
                               + font->headerSize  // skip PSF's header
                               + (*((unsigned char *) s)  < font->numGlyph ? *s : 0) * font->bytesPerGlyph;
        // calculate the offset on screen
        int offs = (y * font->height * screenPitch) + (x * (font->width + 1) * 4);

        int i, j, line, mask;
        int bytesPerLine = (font->width + 7)/8;

        // handle carriage return
        if(*s == '\r') {
            x = 0;
        } else if(*s == '\n') {     // handle new line
            x = 0;
            y++;
        } else if(*s == '\t') {     // handle horizontal TAB
            x += SPACES_PER_TAB;
            if(x >= screenWidth) {
                x = 0;
                y++;
            }
        } else {                    // print character
            for(j = 0; j < font->height;j++) {
                // display one row
                line = offs;
                mask = 1 << (font->width - 1);

                for(i = 0; i < font->width;i++) {
                    // if bit set, we use white color, otherwise black
                    *((unsigned int *)(framebuffer + line)) = ((int)*glyph) & mask ? 0xFFFFFF : 0;
                    mask >>= 1;
                    line += 4;
                }

                // adjust to next line
                glyph += bytesPerLine;
                offs += screenPitch;
            }

            x++;
        }

        // next character
        s++;
    }
}