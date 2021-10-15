/**
 * @file   SLinkedList.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Singly linked list
 * @date   2021-10-05
 *
 * @copyright Copyright (c) 2021
 */
#ifndef SLINKEDLIST_H_
#define SLINKEDLIST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct SLinkedListN SLinkedListN;
typedef struct SLinkedList   SLinkedList;

struct SLinkedListN {
	int32_t data;
	SLinkedListN* next;
};

struct SLinkedList {
	SLinkedListN* first;
};

/**
 * @brief Initialise the Singly linked list. This set the
 *        SLinkedList::first = NULL;
 */
void SLL_Init(SLinkedList* list);
/**
 * @brief Free all the SLinkedList nodes.
 *
 * @param list Singly linked list pointer.
 */
void SLL_Clean(SLinkedList* list);
/**
 * @brief Add new node with given value in ascending order.
 *
 * @param list  Singly Linked List pointer
 * @param value Data to be added.
 * @return [SUCCESS]: value inserted
 *         [FAILED]: INT32_MIN when allocating memory failed.
 */
int32_t SLL_AddNode(SLinkedList* list, int32_t value);
/**
 * @brief Remove the first value in the singly linked list.
 * 
 * @param list Singly linked list to remove from.
 * @return [SUCESS]: value in the node removed
 *         [FAILED]: INT32_MIN when list is empty.
 */
int32_t SLL_RemoveFirst(SLinkedList* list);
/**
 * @brief Remove the last value in the list.
 *
 * @param list Singly linked list to remove from.
 * @return [SUCESS]: value from the removed node.
 *         [FAILED]: INT32_MIN when list is empty.
 */
int32_t SLL_RemoveLast(SLinkedList* list);
/**
 * @brief Print the list
 *
 * @param list Singly linked list to print.
 */
void SLL_Print(SLinkedList* list);

#ifdef __cplusplus
}
#endif
#endif

