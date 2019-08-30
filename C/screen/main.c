#include <stdio.h>

#include "screen.h"
int main(int argc, char *argv[]) {
    createScreen(64, 64);
    writeScreenBits(4, 2 , 1);
    printf("value:%d\n", readScreenBits(4,2)); 
}