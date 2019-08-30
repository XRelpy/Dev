#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "virtual_mem.h"

void taskCStart() {
    U32 taskMem = task_malloc(1024);
    U32 i;
    for (i = 0; i < 1024; i++) {
        task_write(taskMem, i, 'C');
    }
    printf("C: taskStart\n");
}

void taskCLoop() {
    U32 taskMem = task_malloc(1024);
    U32 i;
    for (i = 0; i < 1024; i++) {
        task_write(taskMem, i, 'C' + i);
    }
    printf("C: taskLoop\n");
}

void taskCExit() {
    printf("C: taskExit\n");
}

TASK_INIT(2)() {
    struct task *taskB = (struct task *) vm_malloc(sizeof(struct task));
    taskB->start = &taskCStart;
    taskB->loop = &taskCLoop;
    taskB->exit = &taskCExit;
    register_task(taskB);
    printf("task 2 init\n");
}