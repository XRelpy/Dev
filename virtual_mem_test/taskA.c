#include <stdio.h>
#include <stdlib.h>

#include"task.h"

void taskAStart() {
    printf("A: taskStart\n");
}

void taskALoop() {
    printf("A: taskLoop\n");
}

void taskAExit() {
    printf("A: taskExit\n");
}

TASK_INIT(0)() {
    struct task *taskA = (struct task *) malloc(sizeof(struct task));
    taskA->start = &taskAStart;
    taskA->loop = &taskALoop;
    taskA->exit = &taskAExit;
    register_task(taskA);
    printf("task 0 init\n");
}