/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  DA267A Lab04.
 * @date   2021-10-03
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

#define TEST_ASSERT(test, ...) do {  \
	printf(__VA_ARGS__);             \
	if (!(test)) {                   \
		printf(": Assertion Failed: (%s), func %s, file %s, line %d\n", #test, __FUNCTION__, __FILE__, __LINE__); \
	} else { printf("\tPassed\n"); }} while(0)
#define TEST_RUN(test) do { printf("TEST: %s\n", #test); test(); } while(0)

#include "SLinkedList.h"
#include "DLinkedList.h"

// Singly Linked List BLACK BOX TESTs
void TEST_SLL_Init() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t ret = SLL_RemoveFirst(&list);
	TEST_ASSERT(ret == INT32_MIN,
	            "Expect return to be %d, got %d", INT32_MIN, ret);
}
void TEST_SLL_AddNode() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t const insertVal = 42;
	int32_t ret = SLL_AddNode(&list, insertVal);
	TEST_ASSERT(ret == insertVal,
	            "Insert value in list, expect return %d, got %d",
	            insertVal, ret);

	SLL_Clean(&list);
}
void TEST_SLL_RemoveFirst() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t const insertVal = 1;
	SLL_AddNode(&list, 2);
	SLL_AddNode(&list, 3);
	SLL_AddNode(&list, 4);
	SLL_AddNode(&list, insertVal);
	SLL_AddNode(&list, 3);

	SLL_Print(&list);

	int32_t remove = SLL_RemoveFirst(&list);
	TEST_ASSERT(remove == insertVal,
	            "Insert values in list, expect return %d, got %d",
	            insertVal, remove);

	SLL_Clean(&list);
}
void TEST_SLL_RemoveLast() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t const insertVal = 42;
	SLL_AddNode(&list, 1);
	SLL_AddNode(&list, insertVal);
	SLL_AddNode(&list, 3);
	SLL_AddNode(&list, 6);

	int32_t remove = SLL_RemoveLast(&list);
	TEST_ASSERT(remove == insertVal,
	            "Expect last value to be %d, got %d", insertVal, remove);

	SLL_Clean(&list);
}
// Singly Linked List WHITE BOX TESTs
void TEST_SLL_InitFirstNULL() {
	SLinkedList list;
	SLL_Init(&list);
	TEST_ASSERT(list.first == NULL, "Expect first to be NULL (0): %p", list.first);
}
void TEST_SLL_AddNodes() {
	SLinkedList list;
	int32_t datas[] = {1, 2, 3, 3};
	SLL_Init(&list);
	SLL_AddNode(&list, 1);
	SLL_AddNode(&list, 3);
	SLL_AddNode(&list, 2);
	SLL_AddNode(&list, 3);

	SLinkedListN* node = list.first;
	int32_t i = 0;
	while(node != NULL) {
		int32_t val = datas[i++];
		TEST_ASSERT(node->data == val, "Expect %d to be %d", node->data, val);
		node = node->next;
	}
	SLL_Print(&list);

	SLL_Clean(&list);
}

void TEST_DLL_Init() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t ret = DLL_RemoveFirst(&list);
	TEST_ASSERT(ret == INT32_MIN,
	            "Expect return to be %d, got %d", INT32_MIN, ret);
}
void TEST_DLL_AddNode() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t const insertVal = 42;
	int32_t ret = DLL_AddNode(&list, insertVal);
	TEST_ASSERT(ret == insertVal,
	            "Insert value in list, expect return %d, got %d",
	            insertVal, ret);

	DLL_Clean(&list);
}
void TEST_DLL_RemoveFirst() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t const insertVal = 42;
	DLL_AddNode(&list, insertVal);
	DLL_AddNode(&list, 1);
	DLL_AddNode(&list, 3);
	DLL_AddNode(&list, 2);
	DLL_AddNode(&list, 3);

	DLL_Print(&list, stdout);

	int32_t remove = DLL_RemoveFirst(&list);
	TEST_ASSERT(remove == 1,
	            "Remove first value, expect %d to be %d",
	            1, remove);

	DLL_Clean(&list);
}
void TEST_DLL_RemoveLast() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t const insertVal = 42;
	DLL_AddNode(&list, 1);
	DLL_AddNode(&list, insertVal);

	int32_t remove = DLL_RemoveLast(&list);
	TEST_ASSERT(remove == insertVal,
	            "Expect last value %d to be %d", remove, insertVal);

	DLL_Clean(&list);
}
void TEST_DLL_InitFirstLastNULL() {
	DLinkedList list;
	DLL_Init(&list);

	TEST_ASSERT(list.first == NULL && list.last == NULL,
			"Expect first %p to be %p, last %p to be %p", list.first, NULL, list.last, NULL);
}
// TODO: WHITE BOX TEST for Doubly Linked List

void app_main() {
	printf("Singly Linked List\n");
	printf("-------------------\n");
	printf(" BLACK BOX TEST\n");
	printf(" ---------------\n");
	TEST_RUN(TEST_SLL_Init);
	TEST_RUN(TEST_SLL_AddNode);
	TEST_RUN(TEST_SLL_RemoveFirst);
	TEST_RUN(TEST_SLL_RemoveLast);
	printf(" WHITE BOX TEST\n");
	printf(" ---------------\n");
	TEST_RUN(TEST_SLL_InitFirstNULL);
	TEST_RUN(TEST_SLL_AddNodes);

	printf("\n");

	printf("Doubly Linked List\n");
	printf("-------------------\n");
	printf(" BLACK BOX TEST\n");
	printf(" ---------------\n");
	TEST_RUN(TEST_DLL_Init);
	TEST_RUN(TEST_DLL_AddNode);
	TEST_RUN(TEST_DLL_RemoveFirst);
	TEST_RUN(TEST_DLL_RemoveLast);
	printf(" WHITE BOX TEST\n");
	printf(" ---------------\n");
	TEST_RUN(TEST_DLL_InitFirstLastNULL);
}

