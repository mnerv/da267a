/**
 * @file   BufferQueue.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Buffer Queue Implementation
 * @date   2021-10-17
 *
 * @copyright Copyright (c) 2021
 */
#include "BufferQueue.h"

void BufferQ_Init(BufferQ_t* queue, void* data, int32_t max) {
	queue->head    = 0;
	queue->tail    = 0;
	queue->entries = 0;
	queue->max     = max;
	queue->data    = data;
}

bool BufferQ_Empty(BufferQ_t* queue) {
	return queue->entries == 0;
}

bool BufferQ_Full(BufferQ_t* queue) {
	return queue->entries == queue->max;
}
int32_t BufferQ_Count(BufferQ_t* queue) {
	return queue->entries;
}

bool BufferQ_Enqueue(BufferQ_t* queue, float value) {
	if (BufferQ_Full(queue)) return false;
	float* buffer = (float*)queue->data;
	buffer[queue->tail] = value;
	queue->entries++;
	queue->tail = (queue->tail + 1) % queue->max;
	return true;
}

float BufferQ_Dequeue(BufferQ_t* queue) {
	float* data = (float*)queue->data;
	float value = data[queue->head];
	if (!BufferQ_Empty(queue)) {
		queue->head = (queue->head + 1) % queue->max;
		queue->entries--;
	}
	return value;
}

float BufferQ_Peek(BufferQ_t* queue, int32_t pos) {
	float* data = (float*)queue->data;
	if (-1 < pos && pos < queue->max)
		return data[pos];
	return data[queue->head];
}

