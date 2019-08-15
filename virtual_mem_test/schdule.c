#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "base.h"

static struct task_list *index;
struct task_list *runningTask;

void register_task(struct task *t) {
    /*/ debug
    t->start();
    t->loop();
    t->exit();
    //*/
    struct task_list *temp;

    if (index == NULL) {
        index = (struct task_list *)malloc(sizeof(struct task_list));
        temp = index;
    } else {
        temp = index;
        while (temp->next != NULL) {
            temp = (struct task_list *)temp->next;
        }
        temp->next = (struct task_list *)malloc(sizeof(struct task_list));
        temp = (struct task_list *)temp->next;
    }
    temp->t = t;

    int cnt = 0;
    temp = index;
    while(temp != NULL){
        cnt++;
        temp = (struct task_list *)temp->next;
    }

    // init system context
    t->taskId = BASE_TASK_ID_START + cnt;
    t->taskStatus = TASK_STATUS_START;
    //printf("Total task:%d\n", cnt); 
}

void schdule_task() {
    if (runningTask == NULL) {
        runningTask = index;
    } else {
        runningTask = (struct task_list *)runningTask->next;
    }

    if (runningTask == NULL) {
        runningTask == index;
    }
}

struct task *getCurrentTask() {
    if (runningTask == NULL) {
        return NULL;
    }
    return (runningTask->t);
}

void task_exit() {
    struct task *t = (struct task *)getCurrentTask();
    if ( t != NULL) {
        t->taskStatus = TASK_STATUS_EXIT;
    }
}