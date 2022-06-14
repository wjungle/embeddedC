#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "circularBuffer.h"

#define BUF_SIZE 4

int main()
{
    static uint8_t buf[BUF_SIZE];
    struct sCircularBuffer cb = INIT_CB(buf);
    uint8_t r_data = 0x01;

    
    for (int i = 0; i < 5; ++i) {
        if (!CBisFull(&cb))
            CBWrite(&cb, i+0x20);
        else
            printf("cb is full\n");
    }
    
    printf("size = %d\n", cb.size);
    
    for (int i = 0; i < 5; ++i) {
        if (!CBisEmpty(&cb)) {
            CBRead(&cb, &r_data);
            printf("read data is %x\n", r_data);
        }
        else
            printf("cb is empty\n");
    }
}
