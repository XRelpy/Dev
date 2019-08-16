#include <stdio.h>
#include<unistd.h>
#include <signal.h>
#include <sys/time.h>
#include<stdbool.h>
#include <string.h>

#include "virtual_mem.h"

#include "task.h"
#include "sys.h"

bool schduleFlag = false;
struct task *currentTask;

int runningCycle = 20;

void timer(int sig)
{
    if(SIGALRM == sig)
    {
        //printf("timer\n");
        schdule_task();
        currentTask = getCurrentTask();
        schduleFlag = false;
        if (SYS_TIMER == SYS_TIMER_1) {
            alarm(1);
        }
    }
    if (DEBUG == 1) {
        runningCycle--;
        if (runningCycle == 0) {
            dumpsys();
            printf("DUMPSYS..\n");
            sleep(1);
            exit(1);
        }
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
    //dumpsys();
    // System Start.
    signal(SIGALRM, timer);
    if (SYS_TIMER == SYS_TIMER_2) {
        struct itimerval tick;
        memset(&tick, 0, sizeof(tick));
        tick.it_value.tv_sec = 1;
        tick.it_value.tv_usec = 0;
        tick.it_interval.tv_sec = 1;
        tick.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &tick, NULL);
    } else if (SYS_TIMER == SYS_TIMER_1) {
        alarm(1);
    }

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
        if (SYS_TIMER == SYS_TIMER_0) {
            timer(SIGALRM);
            sleep(1);  
        } 
    }
    return 0;
}