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

#define FALSE 0
#define TRUE  1

enum eError {
    CB_ERROR_BUFFER_FULL,
    CB_ERROR_BUFFER_EMPTY,
    CB_ERROR_BUFFER_OK,
};

/*
struct tElement {
    uint8_t data;
};
*/

struct sCircularBuffer {
    //struct tElement *buf;
    uint8_t *buf;
    uint16_t size;
    uint16_t read;
    uint16_t write;
    uint16_t free;
};

#define INIT_CB(BUF) { \
                    .buf = BUF, \
                    .size = ARR_SZ(BUF), \
                    .read = 0, \
                    .write = 0, \
                    .free = 0, \
                    }

//bool CBInit(struct sCircularBuffer *cb, uint8_t buf[]);
uint16_t CBLengthData(struct sCircularBuffer *cb);
bool CBisFull(struct sCircularBuffer *cb);
bool CBisEmpty(struct sCircularBuffer *cb);
enum eError CBWrite(struct sCircularBuffer *cb, uint8_t data);
enum eError CBRead(struct sCircularBuffer *cb, uint8_t *data);
enum eError CBFree(struct sCircularBuffer *cb);

#endif