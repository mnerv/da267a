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
typedef struct DLinkedListEl DLinkedListEl;
typedef struct DLinkedList   DLinkedList;

struct DLinkedListEl {
	int32_t data;

	DLinkedListEl* prev;
	DLinkedListEl* next;
};

struct DLinkedList {
	DLinkedListEl* first;
	DLinkedListEl* last;
};

void DLL_Init(DLinkedList* list);
int32_t DLL_AddElement(DLinkedList* list, int32_t value);
int32_t DLL_RemoveFirst(DLinkedList* list);
int32_t DLL_RemoveLast(DLinkedList* list);

#ifdef __cplusplus
}
#endif
#endif

