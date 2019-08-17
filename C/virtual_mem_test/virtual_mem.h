#ifndef  _VIRTUAL_MEM_H
#define  _VIRTUAL_MEM_H

#include "sys.h"
/*
    total memory: 64M
    system use memory: HIGHT:2M
    app use memory: LOW：62M
    TLB:   6bit -- 11 bit -- 9bit
 */

#define MEMORY_START 0x0
#define MEMORY_END 0x3ffffff
#define MEMORY_SYS_BASE  0x3e00000

#define MEM_OFFSET (1 << 9)
#define MEM_DIR_VALUE (1<<6)
#define MEM_MID_DIR_VALUE (1<<6)
/*
    memory index:
        u32 flag:  
                ID: 6
                DIR: 6
                PROTECTION:1
                USED:1
        u32:
            TASK_MEM_INDEX:20
            MID_DIR:11
 */
struct virtual_mem_index
{
    U32 RES_1:18,ID:6, DIR:6, PROTECTION:1, USED:1;
    U32 RES_2:11,TASK_MEM_INDEX:10,MID_DIR:11;
} VIRTUAL_MEME_INDEX;

extern  U64 vm_malloc(U32 size);
extern U32 taskLineTableWrite(U32 taskId, U32 size);
extern U32 taskLineTableDataWrite(U32 taskId, U32 pos, U32 offset, U8 data);
extern U32 *vm_write(U32 pos);
extern U32 *vm_read(U32 pos);
extern void mem_init();
extern void dumpsys();
#endif