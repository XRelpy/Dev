#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "virtual_mem.h"
#include "task_line_memory.h"
#include "task.h"
#include "sys.h"

U8 *mem_index;
U8 *mem_sys;
U8 *mem_task;
const U32 pt_size = sizeof(struct virtual_mem_index);
const U32 pg_szie = MEMORY_SYS_BASE / MEM_OFFSET;

U64 vm_malloc(U32 size) {
    U64 ptr;
    U32 page_count = size / MEM_OFFSET + 1;
    bool find_mem = false;
    U32 i;
    for (i = 0; i < pg_szie; i = i + pt_size)  {
        struct virtual_mem_index *p = (struct virtual_mem_index *)(mem_sys + i);
        if (p->USED == 0) {
            if (!find_mem) {
                ptr = mem_index + (p->DIR) * MEM_MID_DIR_VALUE * MEM_OFFSET + p->MID_DIR * MEM_OFFSET;
                find_mem = true;
            }
            p->USED = 1;
            struct task *t = currentTask;
            p->ID = (t == NULL) ? 1 : t->taskId;
            page_count--;
        } 
        if (page_count == 0) {
            break;
        }
    }
    return ptr;
}
U32 *vm_write(U32 pos) {
    return NULL;
}
U32 * vm_read(U32 pos) {
    return NULL;
}

void mem_init() {
    /*
        create a file as a memory map.
    */
    mem_index = (void  *) malloc((MEMORY_END + 1));
    memset(mem_index, 0x0, (MEMORY_END + 1));
    mem_sys = mem_index + MEMORY_SYS_BASE;

    U32 i;
    for (i = 0; i < pg_szie; i = i + pt_size) {
        struct virtual_mem_index *p = (struct virtual_mem_index *)(mem_sys + i);
        p->RES_1 = 0x0;
        p->USED = 0x0;
        p->ID = 0x0;
        p->RES_2 = 0x0;
        p->TASK_MEM_INDEX = 0x0;
        p->DIR = i / MEM_DIR_VALUE;
        p->MID_DIR = i % MEM_MID_DIR_VALUE;
    }
    mem_task = mem_sys + pg_szie * pt_size;
}

U32 taskLineTableWrite(U32 taskId, U32 size) {
    U32 index =0;
    U32 memBlockSize = size / MEM_OFFSET + 1;
    bool offSetIsWrited = false;
    U64 *taskPrt = mem_task + taskId * (TASK_LINE_MEM_NUM) * sizeof(U64);
    U32 ptrSize = sizeof(U64);
    int tPtr = sizeof(struct task_line);
    U32 i;
    for (i = 0; i < TASK_LINE_MEM_NUM; i++) {
        if ((*(taskPrt + ptrSize * i)) == 0) {
            (*taskPrt) = vm_malloc(size);
            index = i;
            break;
        }
    }
        
    /*
    for (int i = 0; i < TASK_LINE_MEM_NUM; i++) {
        if ((*(taskPrt + ptrSize * i)) == 0) {
            (*taskPrt) = vm_malloc(MEM_OFFSET);
            (*(taskPrt + sizeof(U32))) = TASK_TABLE_USED;
            
            for (int i = 0; i < MEM_OFFSET;i += tPtr) {
                struct task_line * data = taskPrt + i;
                if (data->USED == 0) {
                    if (!offSetIsWrited) {
                        data->USED = 1;
                        data->TYPE = TYPE_LINE_OFFSET;
                        data->OFFSET = size;
                        offSetIsWrited = true;
                    } else {
                        if (memBlockSize == 0) {
                            break;
                        } else {
                            data->USED = 1;
                            data->TYPE = TYPE_LINE_PTR;
                            data->OFFSET = size;
                        }
                    }
                }
            }
            break;
        }
    }
    */
    return index;
}

U32 taskLineTableDataWrite(U32 taskId, U32 pos, U32 offset, U8 data) {
    U32 ptrSize = sizeof(U64); 
    printf("write id:%d\n" + (U32)taskId);
    U8 *taskPrt = mem_task + taskId * (TASK_LINE_MEM_NUM) * sizeof(U64);
    
    (*(taskPrt + offset)) = data;
    printf("WRITE DATA:%c addr:%ld\n", (*(taskPrt + offset)), (taskPrt + offset));
    return 0;
}

void dumpsys() {
    FILE *fp = NULL;
    fp = fopen("mem_map.bin", "w+");
    fwrite(mem_index, 1,(MEMORY_END + 1), fp);
    fclose(fp);
}