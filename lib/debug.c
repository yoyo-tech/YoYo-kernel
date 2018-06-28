//
// Created by YoYo kernel team on 26.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

#include "../init/bootFonts/psf.h"
#include <yoyo/arm.h>
#include <yoyo/debug.h>
#include <stdarg.h>

static int x = 0;
static int y = 0;

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
                               + (*((unsigned char *) *s)  < font->numGlyph ? *s : 0) * font->bytesPerGlyph;
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

static unsigned int strlen(const char *s) {
    unsigned int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

static unsigned int itoa(int value, unsigned int radix, unsigned int uppercase, unsigned int unsig,
          char *buffer, unsigned int zero_pad) {
    char	*pbuffer = buffer;
    int	negative = 0;
    unsigned int	i, len;

    /* No support for unusual radixes. */
    if (radix > 16)
        return 0;

    if (value < 0 && !unsig) {
        negative = 1;
        value = -value;
    }

    /* This builds the string back to front ... */
    do {
        int digit = value % radix;
        *(pbuffer++) = (digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
        value /= radix;
    } while (value > 0);

    for (i = (pbuffer - buffer); i < zero_pad; i++)
        *(pbuffer++) = '0';

    if (negative)
        *(pbuffer++) = '-';

    *(pbuffer) = '\0';

    /* ... now we reverse it (could do it recursively but will
     * conserve the stack space) */
    len = (pbuffer - buffer);
    for (i = 0; i < len / 2; i++) {
        char j = buffer[i];
        buffer[i] = buffer[len-i-1];
        buffer[len-i-1] = j;
    }

    return len;
}

struct Buff {
    char *buffer, *pbuffer;
    unsigned int len;
};

static int _putc(int ch, struct Buff *b) {
    if ((unsigned int)((b->pbuffer - b->buffer) + 1) >= b->len)
        return 0;
    *(b->pbuffer++) = ch;
    *(b->pbuffer) = '\0';
    return 1;
}

static int _puts(char *s, unsigned int len, struct Buff *b) {
    unsigned int i;

    if (b->len - (b->pbuffer - b->buffer) - 1 < len)
        len = b->len - (b->pbuffer - b->buffer) - 1;

    /* Copy to buffer */
    for (i = 0; i < len; i++)
        *(b->pbuffer++) = s[i];
    *(b->pbuffer) = '\0';

    return len;
}

int vsnprintf(char *buffer, unsigned int len, const char *fmt, va_list va) {
    struct Buff b;
    char bf[24];
    char ch;

    b.buffer = buffer;
    b.pbuffer = buffer;
    b.len = len;

    while ((ch=*(fmt++))) {
        if ((unsigned int)((b.pbuffer - b.buffer) + 1) >= b.len)
            break;
        if (ch!='%')
            _putc(ch, &b);
        else {
            char zeroPad = 0;
            char *ptr;
            unsigned int len;

            ch=*(fmt++);

            /* Zero padding requested */
            if (ch=='0') {
                ch=*(fmt++);
                if (ch == '\0')
                    goto end;
                if (ch >= '0' && ch <= '9')
                    zeroPad = ch - '0';
                ch=*(fmt++);
            }

            switch (ch) {
                case 0:
                    goto end;

                case 'u':
                case 'd':
                    len = itoa(va_arg(va, unsigned int), 10, 0, (ch=='u'), bf, zeroPad);
                    _puts(bf, len, &b);
                    break;

                case 'x':
                case 'X':
                    len = itoa(va_arg(va, unsigned int), 16, (ch=='X'), 1, bf, zeroPad);
                    _puts(bf, len, &b);
                    break;

                case 'c' :
                    _putc((char)(va_arg(va, int)), &b);
                    break;

                case 's' :
                    ptr = va_arg(va, char*);
                    _puts(ptr, strlen(ptr), &b);
                    break;

                default:
                    _putc(ch, &b);
                    break;
            }
        }
    }
    end:
    return b.pbuffer - b.buffer;
}


int snprintf(char* buffer, unsigned int len, const char *fmt, ...) {
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vsnprintf(buffer, len, fmt, va);
    va_end(va);

    return ret;
}