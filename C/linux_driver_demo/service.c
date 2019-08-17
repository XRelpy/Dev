/*************************************************************************
	> File   : Service.c
	> Author : Mark_Xiao
	> Mail   : Mark_Xiao@xreply.cn
	> Time   : 17/09/13 - 15:38
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>

#include "buffer.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XReply");

static int Service_Init(void) {
    printk(KERN_ALERT "Start Server\n");
    initBuffer();
    return 0;
}

static void Service_Exit(void) {
    printk(KERN_ALERT "Exit Server\n");
}

module_init(Service_Init);
module_exit(Service_Exit);
