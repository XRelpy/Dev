#include <stdio.h>
#include <stdlib.h>

#include"task.h"

void taskCStart() {
    printf("C:taskStart\n");
}

void taskCLoop() {
    printf("C:taskLoop\n");
}

void taskCExit() {
    printf("C:taskExit\n");
}

TASK_INIT(2)() {
    struct task *taskB = (struct task *) malloc(sizeof(struct task));
    taskB->start = &taskCStart;
    taskB->loop = &taskCLoop;
    taskB->exit = &taskCExit;
    register_task(taskB);
    printf("task 2 init\n");
}