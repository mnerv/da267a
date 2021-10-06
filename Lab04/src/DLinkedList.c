#include "DLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

void DLL_Init(DLinkedList* list) {
	list->first = NULL;
	list->last  = NULL;
}
void DLL_Clean(DLinkedList* list) {
	DLinkedListN* node = list->first;
	while(node != NULL) {
		DLinkedListN* tmp = node->next;
		free(node);
		node = tmp;
	}
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
		node->prev       = list->last;
		list->last->next = node;
		list->last       = node;
	}

	return node->data;
}
int32_t DLL_RemoveFirst(DLinkedList* list) {
	if (list->first == NULL) return INT32_MIN;
	DLinkedListN* node = list->first;
	list->first  = node->next;
	int32_t data = node->data;
	free(node);
	return data;
}
int32_t DLL_RemoveLast(DLinkedList* list) {
	if (list->last == NULL) return INT32_MIN;
	DLinkedListN* node = list->last;
	int32_t data = node->data;
	list->last = node->prev;
	if (list->last != NULL) list->last->next = NULL;
	if (node == list->first) list->first = NULL;
	free(node);
	return data;
}
void DLL_Print(DLinkedList* list) {
	DLinkedListN* nextNode = list->first;
	while(nextNode != NULL) {
		printf("%d->", nextNode->data);
		nextNode = nextNode->next;
	}
	if (nextNode == NULL) printf("NULL\n");
	nextNode = list->last;
	while(nextNode != NULL) {
		printf("%d->", nextNode->data);
		nextNode = nextNode->prev;
	}
	if (nextNode == NULL) printf("NULL\n");
}
