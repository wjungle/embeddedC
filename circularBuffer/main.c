#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "circularBuffer.h"

void* u8DataInit(size_t size)
{
    uint8_t* ptr = malloc(sizeof(uint8_t) * size);
    return ptr;
}

void u8DataCpy(void* dest, const void* src)
{
    uint8_t* d = dest;
    const uint8_t*s = src;
    *d = *s;
}

struct private {
    int a;
    int b;
};

void* priDataInit(size_t size)
{
    printf("%s, %d\n", __func__, (int)size);
    struct private* pri = malloc(sizeof(struct private) * size);
    
    return pri;
}

void priDataCpy(void* dest, const void* src)
{
    struct private* d = dest;
    const struct private* s = src;
    d->a = s->a;
    d->b = s->b;
}

int main()
{
    struct sCircularBuffer* cb1 = CBInit(priDataInit, 16, sizeof(struct private));
    struct private first[5] = {{12, 34}, {21, 43}, {13, 24}, {67, 89}, {73, 81}};
    struct private second = {0, 0};
    
    for (int i = 0; i < 5; ++i) {
        if (!CBisFull(cb1))
            CBWrite(cb1, priDataCpy, &first[i]);
        else
            printf("cb is full\n");
    }
    for (int i = 0; i < 5; ++i) {
        if (!CBisEmpty(cb1)) {
            CBRead(cb1, priDataCpy, &second);
            printf("second.a=%d, second.b=%d\n", second.a, second.b);
        }
        else
            printf("cb is empty\n");
    }    
    //CBWrite(cb1, priDataCpy, &first);    
    //CBRead(cb1, priDataCpy, &second);
    //printf("second.a=%d, second.b=%d\n", second.a, second.b);
    CBExit(cb1);
#if 0
    uint8_t rrrr = 5;
    uint8_t wwww = 6;
    
    printf("wwww-rrrr=%X\n", (rrrr-wwww)&(7));
    printf("2wwww-rrrr=%X\n", (rrrr+8-wwww)%8);    
#endif    
    printf("======================================\n");
#if 1
    struct sCircularBuffer* cb = CBInit(u8DataInit, 4, sizeof(uint8_t));
    uint8_t w_data[5] = {0x20, 0x21, 0x22, 0x23, 0x24};
    uint8_t r_data = 0x01;

    for (int i = 0; i < 5; ++i) {
        if (!CBisFull(cb))
            CBWrite(cb, u8DataCpy, &w_data[i]);
        else
            printf("cb is full\n");
    }
    
    printf("size = %d\n", cb->size);
    
    for (int i = 0; i < 5; ++i) {
        if (!CBisEmpty(cb)) {
            CBRead(cb, u8DataCpy, &r_data);
            printf("read data is %x\n", r_data);
        }
        else
            printf("cb is empty\n");
    }
    CBExit(cb);
#endif
}
