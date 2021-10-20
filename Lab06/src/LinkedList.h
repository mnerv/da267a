/**
 * @file   LinkedList.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Linked List Queue
 * @date   2021-10-20
 *
 * @copyright Copyright (c) 2021
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LinkedListN_t LinkedListN_t;
typedef struct LinkedList_t  LinkedList_t;

struct LinkedListN_t {
	int32_t data;
	LinkedListN_t* prev;
	LinkedListN_t* next;
};

struct LinkedList_t {
	LinkedListN_t* first;
	LinkedListN_t* last;
};

void LinkedListQ_Init(LinkedList_t* list);
uint8_t LinkedListQ_Enqueue(LinkedList_t* list, int32_t data);
int32_t LinkedListQ_Dequeue(LinkedList_t* list);
uint8_t LinkedListQ_Empty(LinkedList_t* list);
void LinkedListQ_Clean(LinkedList_t* list);

#ifdef __cplusplus
}
#endif
#endif

