#ifndef  _VIRTUAL_MEM_H
#define  _VIRTUAL_MEM_H

/*
    total memory: 64M
    system use memory: HIGHT:16M 
    app use memory: LOW：48M
    TLB:   6bit -- 11 bit -- 9bit
 */

#define MEMORY_START 0x0
#define MEMORY_END 0x3ffffff
#define MEMORY_SYS_BASE  0x2000000

#define MEM_OFFSET (1 << 9)

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
    unsigned int RES_1:18,ID:6, DIR:6, PROTECTION:1, USED:1;
    unsigned int RES_2:11,TASK_MEM_INDEX:10,MID_DIR:11;
} VIRTUAL_MEME_INDEX;

extern int vm_malloc(int size);
extern int vm_write(int pos);
extern int vm_read(int pos);
extern void mem_init();
extern void dumpsys();
#endif