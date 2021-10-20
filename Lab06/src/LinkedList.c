#include "LinkedList.h"
#include <stdlib.h>

void LinkedListQ_Init(LinkedList_t* list) {
	list->first = NULL;
	list->last  = NULL;
}

uint8_t LinkedListQ_Enqueue(LinkedList_t* list, int32_t data) {
	LinkedListN_t* node = (LinkedListN_t*)malloc(sizeof(LinkedListN_t));
	if (node == NULL) return 0;
	node->data = data;
	node->prev = NULL;
	node->next = NULL;

	if (list->first == NULL && list->last == NULL) {
		list->first = node;
		list->last	= node;
	} else {  // Insert the new node at the last place
		node->prev       = list->last;
		list->last->next = node;
		list->last       = node;
	}
	return 1;
}
int32_t LinkedListQ_Dequeue(LinkedList_t* list) {
	if (list->first == NULL) return INT32_MIN;
	LinkedListN_t* node = list->first;
	list->first  = node->next;
	int32_t data = node->data;
	if (node->next == NULL) {
		list->first = NULL;
		list->last  = NULL;
	}
	free(node);
	return data;
}
void LinkedListQ_Clean(LinkedList_t* list) {
	LinkedListN_t* node = list->first;
	while(node != NULL) {
		LinkedListN_t* tmp = node->next;
		free(node);
		node = tmp;
	}
	list->first = NULL;
	list->last	= NULL;
}

uint8_t LinkedListQ_Empty(LinkedList_t* list) {
	return list->first == NULL && list->last == NULL;
}

