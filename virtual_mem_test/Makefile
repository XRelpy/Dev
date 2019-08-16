PWD := $(shell pwd)

CC=gcc
flag = -std=c11

target=main.o schdule.o task_line_memory.o taskA.o taskB.o taskC.o virtual_mem.o
inc=sys.h task_line_memory.h task.h virtual_mem.h

all:$(target)
	$(CC) $(flag) $(target) -o main

main.o: $(inc)

schdule.o:$(inc)

virtual_mem.o:$(inc)

taskA.o: $(inc)

taskB.o:$(inc)

taskC.o:$(inc)

.PHONY: clean
clean:
	rm *.o main mem_map.bin	
