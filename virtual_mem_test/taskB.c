#include <stdio.h>
#include <stdlib.h>

#include"task.h"
#include"virtual_mem.h"

void taskBStart() {
    U32 taskMem = task_malloc(512);
    for (int i = 0; i < 512; i++) {
        task_write(taskMem, i, 'B');
    }
    printf("B: taskStart\n");
}

void taskBLoop() {
    U32 taskMem = task_malloc(512);
    for (int i = 0; i < 512; i++) {
        task_write(taskMem, i, 'B' + i);
    }
    printf("B: taskLoop\n");
}

void taskBExit() {
    printf("B: taskExit\n");
}

TASK_INIT(1)() {
    struct task *taskB = (struct task *) vm_malloc((sizeof(struct task)));
    taskB->start = &taskBStart;
    taskB->loop = &taskBLoop;
    taskB->exit = &taskBExit;
    register_task(taskB);
    printf("task 1 init\n");
}