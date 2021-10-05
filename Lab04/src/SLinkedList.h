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
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Forward declarations
typedef struct SLinkedListEl SLinkedListEl;
typedef struct SLinkedList   SLinkedList;

struct SLinkedListEl {
	int32_t data;
	SLinkedListEl* next;
};

struct SLinkedList {
	SLinkedListEl* first;
};

void SLL_Init(SLinkedList* list);
void SLL_Clean(SLinkedList* list);
int32_t SLL_AddElement(SLinkedList* list, int32_t value);
int32_t SLL_RemoveFirst(SLinkedList* list);
int32_t SLL_RemoveLast(SLinkedList* list);

#ifdef __cplusplus
}
#endif
#endif

