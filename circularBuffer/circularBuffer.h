/**************************************************************************//**
 * @file     circularBuffer.h
 * @brief    circular buffer
 *
 * @note
 * Making Embedded Systems, chapter 6
 */

#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ARR_SZ(arr) (sizeof(arr)/sizeof(arr[0]))

typedef void* (*cbInit)(size_t size);
typedef void (*cbWrite)(void* dest, const void* src);
typedef void (*cbRead)(void* dest, const void* src);

enum eError {
    CB_ERROR_BUFFER_FULL,
    CB_ERROR_BUFFER_EMPTY,
    CB_ERROR_BUFFER_OK,
};

struct sCircularBuffer {
    uint8_t *buf;
    uint16_t unit;
    uint16_t size;
    uint16_t read;
    uint16_t write;
    uint16_t free;
};

struct sCircularBuffer * CBInit(cbInit init, size_t size, uint16_t unit);
uint16_t CBLengthData(struct sCircularBuffer *cb);
bool CBisFull(struct sCircularBuffer *cb);
bool CBisEmpty(struct sCircularBuffer *cb);
enum eError CBWrite(struct sCircularBuffer *cb, cbWrite wfunc, void* data);
enum eError CBRead(struct sCircularBuffer *cb, cbRead rFunc, void* data);
enum eError CBFree(struct sCircularBuffer *cb);
enum eError CBExit(struct sCircularBuffer *cb);
#endif