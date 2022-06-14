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

#if 0
bool CBInit(struct sCircularBuffer *cb, uint8_t buf[])
{
    cb->buf = buf;
    cb->size = ARR_SZ(buf);
    cb->read = 0;
    cb->write = 0;
    cb->free = 0;
    
    return true;
}
#endif

uint16_t CBLengthData(struct sCircularBuffer *cb)
{
    return ((cb->write - cb->read) & (cb->size - 1));
}

bool CBisFull(struct sCircularBuffer *cb)
{
    if (CBLengthData(cb) == (cb->size - 1))
        return TRUE;
    return FALSE;
}

bool CBisEmpty(struct sCircularBuffer *cb)
{
    if (CBLengthData(cb) == 0)
        return TRUE;
    return FALSE;
}

enum eError CBWrite(struct sCircularBuffer *cb, uint8_t data)
{
    if (CBLengthData(cb) == (cb->size - 1))
        return CB_ERROR_BUFFER_FULL;
    cb->buf[cb->write] = data;
    cb->write = (cb->write + 1) & (cb->size - 1);
    return CB_ERROR_BUFFER_OK;
}

enum eError CBRead(struct sCircularBuffer *cb, uint8_t *data)
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