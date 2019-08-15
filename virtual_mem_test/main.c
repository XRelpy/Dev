#include <stdio.h>
#include<unistd.h>
#include <signal.h>
#include<stdbool.h>

#include "virtual_mem.h"

#include"task.h"

bool schduleFlag = false;
struct task *currentTask;
void timer(int sig)
{
    if(SIGALRM == sig)
    {
        //printf("timer\n");
        schdule_task();
        currentTask = getCurrentTask();
        schduleFlag = false;
        alarm(1);
    }
    return ;
}

void taskInit() {
    INIT_TASK(0);
    INIT_TASK(1);
    INIT_TASK(2);
}

int main(int argv, char *argc[]) {
    printf("memory init.\n");
    mem_init();
    taskInit();
    printf("system running.\n");
    dumpsys();
    // System Start.
    signal(SIGALRM, timer);
    alarm(1);
    while(1) {
        if (!schduleFlag) {
            if (currentTask != NULL) {
                if (currentTask->taskStatus == TASK_STATUS_START) {
                    currentTask->start();
                    currentTask->taskStatus = TASK_STATUS_LOOP;
                } else if (currentTask->taskStatus == TASK_STATUS_LOOP) {
                    currentTask->loop();    
                } else if (currentTask->taskStatus == TASK_STATUS_EXIT) {
                    currentTask->exit();
                    // TODO release task
                }
            }
            schduleFlag = true;          
        }        
    }
    return 0;
}