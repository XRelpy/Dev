#ifndef _TASK_H
#define _TASH_H

#define TASK_INIT(n) extern void _SEG_TASK_##n
#define INIT_TASK(n) _SEG_TASK_##n()

#define TASK_STATUS_START 0
#define TASK_STATUS_LOOP    1
#define TASK_STATUS_EXIT  2

struct task
{
    // Sys context
    int taskId;
    int taskStatus;
    // Task
    void (*start)();
    void (*loop)();
    void (*exit)();
};

struct task_list
{
    struct task *t;
    struct task_list *next;
};

extern void register_task(struct task *t);
extern void schdule_task();
extern struct task *getCurrentTask();
extern void task_exit();
#endif