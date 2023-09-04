/**************************************************************************//**
 * @file     circularBuffer.c
 * @brief    circular buffer
 *
 * @note
 * Making Embedded Systems, chapter 6
 */

#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "circularBuffer.h"

struct sCircularBuffer* CBInit(cbInit init, size_t size, uint16_t unit)
{
    struct sCircularBuffer* cb = malloc(sizeof(struct sCircularBuffer));
    cb->buf = init(size);
    cb->unit = unit;
    cb->size = size;
    cb->read = 0;
    cb->write = 0;
    cb->free = 0;
    
    return cb;
}

uint16_t CBLengthData(struct sCircularBuffer *cb)
{
    //printf(">>> len = %d\n", (cb->write - cb->read) & (cb->size - 1));
    return ((cb->write - cb->read) & (cb->size - 1));
}

bool CBisFull(struct sCircularBuffer *cb)
{
    if (CBLengthData(cb) == (cb->size - 1))
        return true;
    return false;
}

bool CBisEmpty(struct sCircularBuffer *cb)
{
    if (CBLengthData(cb) == 0)
        return true;
    return false;
}

enum eError CBWrite(struct sCircularBuffer *cb, cbWrite wfunc, void* data)
{
    uint8_t offset = cb->write * cb->unit;
    wfunc(&cb->buf[offset], data);
    cb->write = (cb->write + 1) & (cb->size - 1);
    return CB_ERROR_BUFFER_OK;
}

enum eError CBRead(struct sCircularBuffer *cb, cbRead rFunc, void* data)
{
    uint8_t offset = cb->read * cb->unit;
    rFunc(data, &cb->buf[offset]);
    cb->read = (cb->read + 1) & (cb->size - 1);
    return CB_ERROR_BUFFER_OK;
}

enum eError CBFree(struct sCircularBuffer *cb)
{
    if (CBLengthData(cb) == 0)
        return CB_ERROR_BUFFER_EMPTY;
    cb->free = (cb->free + 1) & (cb->size - 1);
    return CB_ERROR_BUFFER_OK;
}

enum eError CBExit(struct sCircularBuffer *cb)
{
    free(cb->buf);
    cb->buf = NULL;
    free(cb);
    cb = NULL;
    
    return CB_ERROR_BUFFER_OK;
}