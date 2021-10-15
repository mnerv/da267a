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

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

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

/**
 * @brief Initialise Doubly linked list.
 *        This set `DLinkedList::first = NULL` and `DLinkedList::last = NULL`.
 */
void DLL_Init(DLinkedList* list);
/**
 * @brief Free the memory in the list.
 */
void DLL_Clean(DLinkedList* list);
/**
 * @brief Add new node in ascending order.
 *
 * @param list  Doubly linked list to be added to.
 * @param value Value to be insert into the node.
 * @return [SUCCESS]: value inserted
 *         [FAILED]:  INT32_MIN when failed to allocating memory.
 */
int32_t DLL_AddNode(DLinkedList* list, int32_t value);
/**
 * @brief Remove the first node in the list
 *
 * @param list Doubly linked list to remove from
 * @return [SUCCESS]: value in the first node
 *         [FAILED]:  INT32_MIN when list is empty
 */
int32_t DLL_RemoveFirst(DLinkedList* list);
/**
 * @brief Remove the last node in the list
 *
 * @param list Doubly linked list to remove from
 * @return [SUCCESS]: value in the last node
 *         [FAILED]:  INT32_MIN when list is empty
 */
int32_t DLL_RemoveLast(DLinkedList* list);
/**
 * @brief Print the doubly linked list layout
 * @param list Doubly linked list to view
 */
void DLL_Print(DLinkedList* list, FILE* output);

#ifdef __cplusplus
}
#endif
#endif

