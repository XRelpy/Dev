#ifndef _TASK_LINE_MEMORY_H
#define _TASK_LINE_MEMORY_H

#include "sys.h"

extern U64 task_malloc(U32 size);
extern U32 task_write(U64 pos, U8 data );
extern U8 task_read(U64 pos);
extern U32 task_freem(U64 pos);
#endif