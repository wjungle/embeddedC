#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "circularBuffer.h"

int main()
{
    struct sCircularBuffer cb;
    struct tElement w_data = {0xff};
    struct tElement w1_data = {0xed};
    struct tElement w2_data = {0xab};
    struct tElement r_data = {0x01};
    
    CBInit(&cb, 1024);
    
    CBWrite(&cb, w_data);
    CBWrite(&cb, w1_data);
    CBWrite(&cb, w2_data);
    
    CBRead(&cb, &r_data);
    printf("read data is %x\n", r_data.data);
    CBRead(&cb, &r_data);
    printf("read data is %x\n", r_data.data);
    CBRead(&cb, &r_data);
    printf("read data is %x\n", r_data.data);
}
