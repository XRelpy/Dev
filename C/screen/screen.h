#ifndef _SCREEN_H
#define _SCREEN_H

// only for one bits of this screen.

#define U8 unsigned char
#define U16 unsigned short int
#define U32 unsigned int

struct screen
{
    U32  width;
    U32 height;
};


extern void createScreen(U32 width, U32 height);
extern U32 writeScreenBits(U32 x, U32 y, U8 bits);
extern U8  readScreenBits(U32 x, U32 y);
extern void dumpScreen();

#endif