#ifndef _TASK_LINE_MEMORY_H
#define _TASK_LINE_MEMORY_H

#include "sys.h"

#define TYPE_LINE_OFFSET 1
#define TYPE_LINE_PTR 2

#define TASK_TABLE_USED 1
#define TASK_TABLE_USED_FULL 2
struct task_line {
    U32 RES:3,OFFSET:26,TYPE:2,USED:1
};

extern U8 *mem_task;
extern U32 task_malloc(U32 size);
extern U32 task_write(U32 pos, U32 offset, U8 data);
extern U8 task_read(U64 pos);
extern U32 task_freem(U64 pos);
#endif