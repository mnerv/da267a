#include "SLinkedList.h"
#include <stdlib.h>

void SLL_Init(SLinkedList* list) {
	list->first = NULL;
}
void SLL_Clean(SLinkedList* list) {
	SLinkedListEl* next = list->first;
	while(next != NULL) {
		SLinkedListEl* cur = next;
		next = next->next;
		free(cur);
	}
}
int32_t SLL_AddElement(SLinkedList* list, int32_t value) {
	return INT32_MIN;
}
int32_t SLL_RemoveFirst(SLinkedList* list) {
	return INT32_MIN;
}
int32_t SLL_RemoveLast(SLinkedList* list) {
	return INT32_MIN;
}

