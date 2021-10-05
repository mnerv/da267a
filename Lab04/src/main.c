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
		printf("Assertion Failed: (%s), func %s, file %s, line %d\n", #test, __FUNCTION__, __FILE__, __LINE__); \
	} else { printf("\tPassed\n"); }} while(0)
#define TEST_RUN(test) do { printf("TEST: %s\n", #test); test(); } while(0)

#include "SLinkedList.h"
#include "DLinkedList.h"

void TEST_SLL_Init() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t ret = SLL_RemoveFirst(&list);
	TEST_ASSERT(ret == INT32_MIN,
	            "\tExpect return to be %d, got %d", INT32_MIN, ret);
}
void TEST_SLL_AddElement() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t const insertVal = 42;
	int32_t ret = SLL_AddElement(&list, insertVal);
	TEST_ASSERT(ret == insertVal,
	            "\tInsert value in list, expect return %d, got %d",
	            insertVal, ret);
	SLL_Clean(&list);
}
void TEST_SLL_RemoveFirst() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t const insertVal = 42;
	SLL_AddElement(&list, insertVal);
	SLL_AddElement(&list, 1);
	int32_t remove = SLL_RemoveFirst(&list);
	TEST_ASSERT(remove == insertVal,
	            "\tInsert value in list, expect return %d, got %d",
	            insertVal, remove);

	SLL_Clean(&list);
}
void TEST_SLL_RemoveLast() {
	SLinkedList list;
	SLL_Init(&list);
	int32_t const insertVal = 42;
	SLL_AddElement(&list, 1);
	SLL_AddElement(&list, insertVal);

	int32_t remove = SLL_RemoveLast(&list);
	TEST_ASSERT(remove == insertVal,
	            "\tExpect last value to be %d, got %d", insertVal, remove);

	SLL_Clean(&list);
}
// TODO: WHITE BOX TEST for Singly Linked List

void TEST_DLL_Init() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t ret = DLL_RemoveFirst(&list);
	TEST_ASSERT(ret == INT32_MIN,
	            "\tExpect return to be %d, got %d", INT32_MIN, ret);
}
void TEST_DLL_AddElement() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t const insertVal = 42;
	int32_t ret = DLL_AddElement(&list, insertVal);
	TEST_ASSERT(ret == insertVal,
	            "\tInsert value in list, expect return %d, got %d",
	            insertVal, ret);
}
void TEST_DLL_RemoveFirst() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t const insertVal = 42;
	DLL_AddElement(&list, insertVal);
	DLL_AddElement(&list, 1);
	int32_t remove = DLL_RemoveFirst(&list);
	TEST_ASSERT(remove == insertVal,
	            "\tInsert value in list, expect return %d, got %d",
	            insertVal, remove);
}
void TEST_DLL_RemoveLast() {
	DLinkedList list;
	DLL_Init(&list);
	int32_t const insertVal = 42;
	DLL_AddElement(&list, 1);
	DLL_AddElement(&list, insertVal);

	int32_t remove = DLL_RemoveLast(&list);
	TEST_ASSERT(remove == insertVal,
	            "\tExpect last value to be %d, got %d", insertVal, remove);
}
// TODO: WHITE BOX TEST for Doubly Linked List

void app_main() {
	printf("Singly Linked List\n");
	printf("-------------------\n");
	printf(" BLACK BOX TEST\n");
	printf(" ---------------\n");
	TEST_RUN(TEST_SLL_Init);
	TEST_RUN(TEST_SLL_AddElement);
	TEST_RUN(TEST_SLL_RemoveFirst);
	TEST_RUN(TEST_SLL_RemoveLast);
	printf(" WHITE BOX TEST\n");
	printf(" ---------------\n");

	printf("\n");

	printf("Doubly Linked List\n");
	printf("-------------------\n");
	printf(" BLACK BOX TEST\n");
	printf(" ---------------\n");
	TEST_RUN(TEST_DLL_Init);
	TEST_RUN(TEST_DLL_AddElement);
	TEST_RUN(TEST_DLL_RemoveFirst);
	TEST_RUN(TEST_DLL_RemoveLast);
	printf(" WHITE BOX TEST\n");
	printf(" ---------------\n");
}

