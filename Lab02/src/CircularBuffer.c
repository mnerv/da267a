/**
 * @file   CircularBuffer.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Circular Buffer implemenation with int32_t.
 *         This only stores up to BUFFER_SIZE - 1.
 * @date   2021-09-15
 *
 * @copyright Copyright (c) 2021
 */
#include "CircularBuffer.h"
#include <stdio.h>

void InitCircularBuffer(CircularBuffer* buffer, int32_t* data, int32_t maxLength) {
	buffer->data      = data;
	buffer->maxLength = maxLength;
	buffer->head = 0;
	buffer->tail = 0;
}
int32_t CircularBufferContains(CircularBuffer* buffer, int32_t value) {
	for (int32_t i = buffer->head; i != buffer->tail; i = (i + 1) % buffer->maxLength)
		if (buffer->data[i] == value)
			return value;
	return INT32_MIN;
}
int32_t CircularBufferAddElement(CircularBuffer* buffer, int32_t value) {
	int32_t tail = (buffer->tail + 1) % buffer->maxLength;
	if (tail == buffer->head)
		return INT32_MIN;
	buffer->data[buffer->tail] = value;
	buffer->tail = (buffer->tail + 1) % buffer->maxLength;
	return value;
}
int32_t CircularBufferRemoveValue(CircularBuffer* buffer, int32_t value) {
	int32_t it    = buffer->head;
	int32_t count = 0;
	while(it != buffer->tail) {
		if (buffer->data[it] == value) {
			count++;
			buffer->data[it] = buffer->data[(it + 1) % buffer->maxLength];
		}
		it = (it + 1) % buffer->maxLength;
	}
	buffer->tail = (buffer->head + (count - 1)) % buffer->maxLength;

	return count == 0 ? INT32_MIN : value;
}
int32_t CircularBufferRemoveHead(CircularBuffer* buffer) {
	if (buffer->head == buffer->tail)
		return INT32_MIN;
	int32_t re = buffer->data[buffer->head];
	buffer->head = (buffer->head + 1) % buffer->maxLength;
	return re;
}
void CircularBufferPrint(CircularBuffer* buffer) {
	for	(int32_t i = buffer->head; i != buffer->tail; i = (i + 1) % buffer->maxLength) {
		printf("| %d ", buffer->data[i]);
	}
	printf("|\n");
}

