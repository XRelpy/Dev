#include "task_line_memory.h"
#include "virtual_mem.h"
#include "task.h"

U32 getTaskId() {
    struct task *t = getRuningTask();
    U32 taskId = t->taskId - BASE_TASK_ID_START;
    return taskId;
}

U32 task_malloc(U32 size) {
    return taskLineTableWrite(getTaskId(), size);
 }
U32 task_write(U32 pos, U32 offset, U8 data) {
    taskLineTableDataWrite(getTaskId(),pos, offset, data);
    return 0;
}
U8 task_read(U64 pos) {
    return 0;
}
U32 task_freem(U64 pos) {
    return 0;
}