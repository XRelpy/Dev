#include <stdio.h>
#include <stdlib.h>

#include"task.h"
#include "task_line_memory.h"
#include"virtual_mem.h"

void taskAStart() {
    U32 taskMem = task_malloc(256);
    U32 i;
    for (i = 0; i < 256; i++) {
        task_write(taskMem, i, 'A');
    }
    printf("A: taskStart\n");
}

void taskALoop() {
    
    U32 taskMem = task_malloc(256);
    U32 i;
    for (i = 0; i < 256; i++) {
        task_write(taskMem, i, 'A' + i);
    }
    /*
    U32 taskMem = task_malloc(512);
    for (int i = 0; i < 512; i++) {
        task_write(taskMem, i, 'A');
    }*/
    printf("A: taskLoop\n");
}

void taskAExit() {
    printf("A: taskExit\n");
}

TASK_INIT(0)() {
    struct task *taskA = (struct task *) vm_malloc(sizeof(struct task));
    taskA->start = &taskAStart;
    taskA->loop = &taskALoop;
    taskA->exit = &taskAExit;
    register_task(taskA);
    printf("task 0 init\n");
}