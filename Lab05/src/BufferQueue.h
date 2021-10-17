/**
 * @file   BufferQueue.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Buffer Queue
 * @date   2021-10-16
 *
 * @copyright Copyright (c) 2021
 */
#ifndef BUFFER_QUEUE_H_
#define BUFFER_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_EMPTY INT32_MIN

typedef struct {
	int32_t head;
	int32_t tail;
	int32_t entries;
	int32_t max;
	void*  data;
} BufferQ_t;

void BufferQ_Init(BufferQ_t* queue, void* data, int32_t max);
bool BufferQ_Empty(BufferQ_t* queue);
bool BufferQ_Full(BufferQ_t* queue);

bool BufferQ_Enqueue(BufferQ_t* queue, float value);
float BufferQ_Dequeue(BufferQ_t* queue);

#ifdef __cplusplus
}
#endif
#endif

