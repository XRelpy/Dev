/*************************************************************************
	> File   : buffer.h
	> Author : Mark_Xiao
	> Mail   : Mark_Xiao@xreply.cn
	> Time   : 17/09/13 - 16:20
 ************************************************************************/

#ifndef _BUFFER_H
#define _BUFFER_H
#include <linux/list.h>
#include <linux/slab.h>

#define TAG "buffer"

extern void writeBuffer(unsigned char *data);
extern void initBuffer(void);
#endif
