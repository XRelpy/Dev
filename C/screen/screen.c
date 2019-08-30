#include <stdlib.h>
#include "screen.h"

#define BITS_MASK 0x00000001
struct screen   *s;
U32 *screen_buf;

void createScreen(U32 width, U32 height) {
    s = (struct screen *)malloc(sizeof(struct screen));
    s->height = height;
    s->width = width;

    screen_buf = (U32 *)malloc(width * height /  8 + 1);
}

    U32 writeScreenBits(U32 x, U32 y, U8 bits) {
        if (x > (s->width) ||  (y > s->width)) {
            return -1;
        }

        U32 wv = bits & BITS_MASK;
        U32 pix = x + y * (s->width);
        U32 pos = pix / 32;
        U32 value  = *(screen_buf + pos);
        *(screen_buf + pos) = value | (wv << (pix % 32));
        return 0;
    }

    U8  readScreenBits(U32 x, U32 y) {
         U32 pix = x + y * (s->width);
         U32 pos = pix / 32;
         U32 value =   *(screen_buf + pos);
         return (value >> (pix % 32)) & BITS_MASK;
    }

    void dumpScreen() {
    }