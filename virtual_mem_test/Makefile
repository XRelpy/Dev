PWD := $(shell pwd)

all: main.o virtual_mem.o schdule.o taskA.o taskB.o taskC.o
	gcc -C main.o virtual_mem.o  schdule.o taskA.o taskB.o taskC.o -o main

virtual_mem.o:virtual_mem.c  virtual_mem.h
	gcc -c  virtual_mem.c	

schdule.o: schdule.c task.h
	gcc -c 	schdule.c

taskA.o : taskA.c task.h
	gcc -c taskA.c

taskB.o : taskB.c task.h
	gcc -c taskB.c
taskC.o : taskC.c task.h
	gcc -c taskC.c

.PHONY: clean
clean:
	rm *.o main mem_map.bin	