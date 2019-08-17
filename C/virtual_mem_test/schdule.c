#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include"virtual_mem.h"
#include "sys.h"

static struct task_list *index;
struct task_list *runningTask;
U32 taskCnt = 1;

void register_task(struct task *t) {
    /*/ debug
    t->start();
    t->loop();
    t->exit();
    //*/
    struct task_list *temp;

    if (index == NULL) {
        index = (struct task_list *)vm_malloc(sizeof(struct task_list));
        index->next = NULL;
        temp = index;
    } else {
        temp = index;
        while (temp->next != NULL) {
            temp = (struct task_list *)temp->next;
        }
        temp->next = (struct task_list *)vm_malloc(sizeof(struct task_list));
        temp = (struct task_list *)temp->next;
        temp->next = NULL;
    }
    // init system context
    t->taskId = BASE_TASK_ID_START + taskCnt;
    t->taskStatus = TASK_STATUS_START;
    temp->t = t;
    taskCnt++;

    int cnt = 0;
    temp = index;
    while(temp != NULL){
        cnt++;
        temp = (struct task_list *)temp->next;
    }

    //printf("Total task:%d\n", cnt); 
}

void schdule_task() {
    if (runningTask != NULL) {
        runningTask = (struct task_list *)runningTask->next;
    }

    if (runningTask == NULL) {
        runningTask = index;
    }
}

struct task *getRuningTask() {
    return (runningTask->t);
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
        t->taskStatus = TASK_STATUS_PRE_EXIT;
    }
}