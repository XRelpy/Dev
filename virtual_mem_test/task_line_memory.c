#include <stdbool.h>
#include <stdio.h>
#include "task_line_memory.h"
#include "virtual_mem.h"
#include "task.h"

U32 getTaskId() {
    struct task *t = currentTask;
    U32 taskId = t->taskId - BASE_TASK_ID_START;
    return taskId;
}

U32 task_malloc(U32 size) {
    U32 index =0;  
    U32 memBlockSize = size / MEM_OFFSET + 1;
    bool offSetIsWrited = false;
    U32 taskId = getTaskId();
    U64 *taskPrt = mem_task + taskId * (TASK_LINE_MEM_NUM) * sizeof(U64);
    //printf("Base ADDR:%ld\n", *taskPrt);
    U32 ptrSize = sizeof(U64);
    //int tPtr = sizeof(struct task_line);
    for (U32 i = 0; i < TASK_LINE_MEM_NUM; i++) {
        //*(taskPrt + i) = 'A';
        if ((*(taskPrt + i)) == 0) {
            (*(taskPrt + i)) = vm_malloc(size);
             //printf("Base ADDR Malloc:%ld\n", *(taskPrt + i)); 
            
            U8 *data = *(taskPrt + i);
            (*data) = 'D';
            //printf("ADDR:%ld\n", *(taskPrt + i));
            //printf("taskId:%d\n", taskId);
            index = i;
            break;
        }
    }
    //printf("Index:%d\n", index);
    return index;
}

U32 task_write(U32 pos, U32 offset, U8 data) {
    U32 ptrSize = sizeof(U64); 
    U32 taskId = getTaskId();
    U64 *taskPrt = mem_task + (taskId * (TASK_LINE_MEM_NUM)) * sizeof(U64);
    //printf("Write Base ADDR:%ld\n", *taskPrt);
    //printf("Write Base ADDR2 :%ld %d\n", *(taskPrt + pos), pos);
     //printf("Base ADDR Write:%ld\n", *(taskPrt + pos)); 
       if (*(taskPrt + pos) == 0) return -1;
    U8 *t = *(taskPrt + pos);
    *(t + offset) = data; 
    return 0;
}
U8 task_read(U64 pos) {
    return 0;
}
U32 task_freem(U64 pos) {
    return 0;
}