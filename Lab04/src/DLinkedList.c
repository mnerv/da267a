#include "DLinkedList.h"
#include <stdlib.h>

void Swap_Int32(int32_t* a, int32_t* b) {
	int32_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void DLL_Init(DLinkedList* list) {
	list->first = NULL;
	list->last	= NULL;
}
void DLL_Clean(DLinkedList* list) {
	DLinkedListN* node = list->first;
	while(node != NULL) {
		DLinkedListN* tmp = node->next;
		free(node);
		node = tmp;
	}
	list->first = NULL;
	list->last	= NULL;
}
int32_t DLL_AddNode(DLinkedList* list, int32_t value) {
	DLinkedListN* node = (DLinkedListN*)malloc(sizeof(DLinkedListN));
	if (node == NULL) return INT32_MIN;
	node->data = value;
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

	DLinkedListN* cn = list->first;
	DLinkedListN* pn = NULL;

	// Bubble sort
	while(cn != NULL) {
		uint8_t swapped = 0;
		cn = list->first;
		while (cn != pn && cn->next != NULL) {
			if (cn->data > cn->next->data) {
				Swap_Int32(&cn->data, &cn->next->data);
				swapped = 1;
			}
			cn = cn->next;
		}
		pn = cn;
		if (!swapped) break;
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
void DLL_Print(DLinkedList* list, FILE* output) {
	DLinkedListN* nextNode = list->first;
	fprintf(output, "start: ");
	while(nextNode != NULL) {
		fprintf(output, "%d->", nextNode->data);
		nextNode = nextNode->next;
	}
	if (nextNode == NULL) fprintf(output, "NULL\n");
	nextNode = list->last;
	fprintf(output, "end:   ");
	while(nextNode != NULL) {
		fprintf(output, "%d->", nextNode->data);
		nextNode = nextNode->prev;
	}
	if (nextNode == NULL) fprintf(output, "NULL\n");
}

