/*************************************************************************
	> File   : buffer.c
	> Author : Mark_Xiao
	> Mail   : Mark_Xiao@xreply.cn
	> Time   : 17/09/13 - 16:18
 ************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>

#include "buffer.h"

void writeBuffer(unsigned char *data) {
    //printk(KERN_ALERT "writeBuffer\n");
}

void initBuffer(void) {
    printk(KERN_ALERT "init Buffer\n");
}
