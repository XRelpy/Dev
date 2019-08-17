

obj-m += Service.o
Service-objs +=service.o buffer.o
#obj-buffer += Buffer/
LINUX_KERNEL := $(shell uname -r)
#KDIR := /usr/src/linux-headers-$(LINUX_KERNEL)/
KDIR := /lib/modules/$(LINUX_KERNEL)/build
PWD := $(shell pwd)

all: 
	make -C $(KDIR) M=$(PWD) modules 
clean:
	rm -rf *.ko *.o *.mod *.mod.c *.symvers modules.order
install:
	insmod Service.ko
uninstall:
	rmmod Service.ko
