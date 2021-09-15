/**
 * @file   CircularBuffer.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Circular Buffer interface with int32_t with max
 *         size being BUFFER_SIZE - 1. This is the limitation
 *         of storing only head and tail counters.
 * @date   2021-09-15
 *
 * @copyright Copyright (c) 2021
 */
#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdint.h>

typedef struct {
	int32_t* data;
	int32_t  head;
	int32_t  tail;
	int32_t  maxLength;
} CircularBuffer;

void InitCircularBuffer(CircularBuffer* buffer, int32_t* data, int32_t maxLength);
int32_t CircularBufferContains(CircularBuffer* buffer, int32_t value);
int32_t CircularBufferAddElement(CircularBuffer* buffer, int32_t value);
int32_t CircularBufferRemoveValue(CircularBuffer* buffer, int32_t value);
int32_t CircularBufferRemoveHead(CircularBuffer* buffer);
void CircularBufferPrint(CircularBuffer* buffer);

#endif

