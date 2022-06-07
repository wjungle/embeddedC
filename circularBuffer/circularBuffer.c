/**************************************************************************//**
 * @file     circularBuffer.c
 * @brief    circular buffer
 *
 * @note
 * Making Embedded Systems, chapter 6
 */
 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "circularBuffer.h"

bool CBInit(struct sCircularBuffer *cb, uint16_t size)
{
    cb->size = size;
    cb->read = 0;
    cb->write = 0;
    cb->free = 0;
    
    return true;
}

uint16_t CBLengthData(struct sCircularBuffer *cb)
{
    return ((cb->write - cb->read) & (cb->size - 1));
}

enum eError CBWrite(struct sCircularBuffer *cb, struct tElement data)
{
    if (CBLengthData(cb) == (cb->size - 1))
        return CB_ERROR_BUFFER_FULL;
    cb->buf[cb->write] = data;
    cb->write = (cb->write + 1) & (cb->size - 1);
    return CB_ERROR_BUFFER_OK;
}

enum eError CBRead(struct sCircularBuffer *cb, struct tElement *data)
{
    if (CBLengthData(cb) == 0)
        return CB_ERROR_BUFFER_EMPTY;
    *data = cb->buf[cb->read];
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