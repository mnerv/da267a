#include "DLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

void DLL_Init(DLinkedList* list) {
	list->first = NULL;
	list->last  = NULL;
}
int32_t DLL_AddNode(DLinkedList* list, int32_t value) {
	DLinkedListN* node = (DLinkedListN*)malloc(sizeof(DLinkedListN));
	if (node == NULL) return INT32_MIN;
	node->data = value;
	node->prev = NULL;
	node->next = NULL;

	if (list->first == NULL && list->last == NULL) {
		list->first = node;
		list->last  = node;
	} else {
		list->last->next = node;
		list->last = node;
	}

	return node->data;
}
int32_t DLL_RemoveFirst(DLinkedList* list) {
	return INT32_MIN;
}
int32_t DLL_RemoveLast(DLinkedList* list) {
	return INT32_MIN;
}
void DLL_Print(DLinkedList* list) {
	DLinkedListN* nextNode = list->first;
	while(nextNode != NULL) {
		printf("%d->", nextNode->data);
		nextNode = nextNode->next;
	}
	if (nextNode == NULL) printf("NULL\n");
}

