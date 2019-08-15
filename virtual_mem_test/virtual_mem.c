#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "virtual_mem.h"
#include "task.h"

unsigned char *mem_index;
unsigned char *mem_sys;
unsigned char *mem_task;
const int pt_size = sizeof(struct virtual_mem_index);
const int pg_szie = MEMORY_SYS_BASE / MEM_OFFSET;

 unsigned long  vm_malloc(unsigned int size) {
    unsigned long ptr;
    int page_count = size / MEM_OFFSET + 1;
    printf("size:%d\n", page_count);
    bool find_mem = false;
        for (int i = 0; i < pg_szie; i = i + pt_size)  {
            struct virtual_mem_index *p = (struct virtual_mem_index *)(mem_sys + i);
            if (p->USED == 0) {
                    if (!find_mem) {
                        ptr = mem_index + (p->DIR) * (p->MID_DIR) * MEM_OFFSET +(p->MID_DIR) * MEM_OFFSET ;
                        find_mem = true;
                        printf("index0:%lld\n", ptr);
                        //printf("index:%lld\n", (mem_index + (p->DIR) * (p->MID_DIR) * MEM_OFFSET));
                    }
                    p->USED = 1;
                    p->ID = 1;
                    page_count--;
            } 
            if (page_count == 0) {
                break;
            }
    }
    return ptr;
}
int *vm_write(unsigned int pos) {
    return NULL;
}
int * vm_read(unsigned int pos) {
    return NULL;
}

void mem_init() {
    /*
        create a file as a memory map.
    */
    mem_index = (void  *) malloc((MEMORY_END + 1));
    memset(mem_index, 0x0, (MEMORY_END + 1));
    // init gpt
    printf("virtual_mem_index:%ld\n" ,mem_index);
    mem_sys = mem_index + MEMORY_SYS_BASE;


    for (int i = 0; i < pg_szie; i = i + pt_size) {
        struct virtual_mem_index *p = (struct virtual_mem_index *)(mem_sys + i);
        p->RES_1 = 0x0;
        p->USED = 0x0;
        p->ID = 0x0;
        p->RES_2 = 0x0;
        p->TASK_MEM_INDEX = 0x0;
        p->DIR = i / MEM_DIR_VALUE;
        p->MID_DIR = i % MEM_MID_DIR_VALUE;
        printf("pg： %d %d\n",p->DIR, p->MID_DIR);
    }
    mem_task = mem_sys + pg_szie * pt_size;
    //dumpsys();
}

void dumpsys() {
    FILE *fp = NULL;
    fp = fopen("mem_map.bin", "w+");
    fwrite(mem_index, 1,(MEMORY_END + 1), fp);
    fclose(fp);
}