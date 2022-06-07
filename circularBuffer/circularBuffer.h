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

enum eError {
    CB_ERROR_BUFFER_FULL,
    CB_ERROR_BUFFER_EMPTY,
    CB_ERROR_BUFFER_OK,
};

struct tElement {
    uint8_t data;
};

struct sCircularBuffer {
    struct tElement *buf;
    uint16_t size;
    uint16_t read;
    uint16_t write;
    uint16_t free;
};

bool CBInit(struct sCircularBuffer *cb, uint16_t size);
uint16_t CBLengthData(struct sCircularBuffer *cb);
enum eError CBWrite(struct sCircularBuffer *cb, struct tElement data);
enum eError CBRead(struct sCircularBuffer *cb, struct tElement *data);
enum eError CBFree(struct sCircularBuffer *cb);

#endif