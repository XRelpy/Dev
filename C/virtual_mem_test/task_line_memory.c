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
    U32 ptrSize = sizeof(U64);
    U32 i;
    for (i = 0; i < TASK_LINE_MEM_NUM; i++) {
        if ((*(taskPrt + i)) == 0) {
            (*(taskPrt + i)) = vm_malloc(size);
            index = i;
            break;
        }
    }
    return index;
}

U32 task_write(U32 pos, U32 offset, U8 data) {
    U32 ptrSize = sizeof(U64); 
    U32 taskId = getTaskId();
    U64 *taskPrt = mem_task + (taskId * (TASK_LINE_MEM_NUM)) * sizeof(U64);
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