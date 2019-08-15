#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual_mem.h"
#include "task.h"

unsigned char *mem_index;
unsigned char *mem_sys;
unsigned char *mem_task;

int vm_malloc(int size) {
    int taskId = getCurrentTask();
    return NULL;
}
int vm_write(int pos) {
    return NULL;
}
int  vm_read(int pos) {
    return NULL;
}

void mem_init() {
    /*
        create a file as a memory map.
    */
    mem_index = (unsigned char  *) malloc((MEMORY_END + 1));
    memset(mem_index, 0x0, (MEMORY_END + 1));
    // init gpt
    printf("virtual_mem_index:%ld\n" ,sizeof(VIRTUAL_MEME_INDEX));
    mem_sys = mem_index + MEMORY_SYS_BASE;

    const int pt_size = sizeof(struct virtual_mem_index);
    const int pg_szie = MEMORY_SYS_BASE / MEM_OFFSET;
    for (int i = 0; i < pg_szie; i = i + pt_size) {
        struct virtual_mem_index *p = (struct virtual_mem_index *)(mem_sys + i);
        p->RES_1 = 0x0;
        p->USED = 0x0;
        p->ID = 0x0;
        p->RES_2 = 0x0;
        p->TASK_MEM_INDEX = 0x0;
        p->MID_DIR = 0x0;
    }
    //dumpsys();
}

void dumpsys() {
    FILE *fp = NULL;
    fp = fopen("mem_map.bin", "w+");
    fwrite(mem_index, 1,(MEMORY_END + 1), fp);
    fclose(fp);
}