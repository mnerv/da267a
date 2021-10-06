/**
 * @file   DLinkedList.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Doubly linked list
 * @date   2021-10-05
 *
 * @copyright Copyright (c) 2021
 */
#ifndef DLINKEDLIST_H_
#define DLINKEDLIST_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Forward declarations
typedef struct DLinkedListN DLinkedListN;
typedef struct DLinkedList  DLinkedList;

struct DLinkedListN {
	int32_t data;

	DLinkedListN* prev;
	DLinkedListN* next;
};

struct DLinkedList {
	DLinkedListN* first;
	DLinkedListN* last;
};

void DLL_Init(DLinkedList* list);
int32_t DLL_AddNode(DLinkedList* list, int32_t value);
int32_t DLL_RemoveFirst(DLinkedList* list);
int32_t DLL_RemoveLast(DLinkedList* list);

#ifdef __cplusplus
}
#endif
#endif

