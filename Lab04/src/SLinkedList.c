#include "SLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

void SLL_Init(SLinkedList* list) {
	list->first = NULL;
}
void SLL_Clean(SLinkedList* list) {
	if (list->first == NULL) return;
	SLinkedListN* next = list->first;
	while(next->next != NULL) {
		SLinkedListN* cur = next;
		next = next->next;
		free(cur);
	}
}
int32_t SLL_AddNode(SLinkedList* list, int32_t value) {
	SLinkedListN* node = (SLinkedListN*)malloc(sizeof(SLinkedListN));
	if (node == NULL) return INT32_MIN;
	node->next = NULL;
	node->data = value;

	if (list->first == NULL) {
		list->first = node;
	} else {
		if (list->first->data > node->data) {
			node->next  = list->first;
			list->first = node;
		} else {
			SLinkedListN* cn = list->first;
			while(cn != NULL) {
				if (cn->next == NULL) {
					cn->next = node;
					break;
				}
				if (cn->data < node->data && cn->next->data > node->data) {
					SLinkedListN* tmp = cn->next;
					cn->next = node;
					node->next = tmp;
					break;
				}
				cn = cn->next;
			}
		}
	}
	return node->data;
}
int32_t SLL_RemoveFirst(SLinkedList* list) {
	if (list->first == NULL) return INT32_MIN;
	SLinkedListN* tmp = list->first->next;
	int32_t value = list->first->data;
	free(list->first);
	list->first = tmp;
	return value;
}
int32_t SLL_RemoveLast(SLinkedList* list) {
	if (list->first == NULL) return INT32_MIN;
	SLinkedListN* tmp = list->first;
	while(tmp->next != NULL) tmp = tmp->next;
	int32_t value = tmp->data;
	free(tmp);
	return value;
}

void SLL_Print(SLinkedList* list) {
	SLinkedListN* nextNode = list->first;
	while(nextNode != NULL) {
		printf("%d->", nextNode->data);
		nextNode = nextNode->next;
	}
	if (nextNode == NULL) printf("NULL\n");
}

