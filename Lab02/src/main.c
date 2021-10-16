/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Lab02 - Circular Buffers
 * @date   2021-09-13
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>
#include <assert.h>

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

#include "CircularBuffer.h"
#define BUFFER_SIZE 4

#define TEST_ASSERT(test, ...) do { \
    printf(__VA_ARGS__);            \
    if (!(test)) {                  \
        printf("Assertion Failed: (%s), func %s, file %s, line %d\n", #test, __FUNCTION__, __FILE__, __LINE__); \
    } else { printf("\tPassed\n"); }} while(0)
#define TEST_RUN(test) do { printf("TEST: %s\n", #test); test(); } while(0)

/**
 * Sleep for amount of ms
 *
 * @param ms Amount of time to sleep in ms.
 */
void sleep_ms(uint32_t ms) {
	TickType_t delay = ms / portTICK_PERIOD_MS;
	vTaskDelay(delay);
}

//
// Black Box 01
//
// Add one element and remove one
// chech if the remove and add are the same.
void TestAddAndRemoveElement() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t add    = CircularBufferAddElement(&buffer, 3);
	int32_t remove = CircularBufferRemoveHead(&buffer);
	TEST_ASSERT(add == remove, "\tTest Add and Remove from buffer");
}

//
// Black Box 02
//
// Add 2 different value into the buffer
// Remove the 2 element
// Check if the 2 removed are in the same order as added.
void TestAddTwoDifferentValue() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t add01 = CircularBufferAddElement(&buffer, 3);
	int32_t add02 = CircularBufferAddElement(&buffer, 2);
	int32_t remove01 = CircularBufferRemoveHead(&buffer);
	int32_t remove02 = CircularBufferRemoveHead(&buffer);

	TEST_ASSERT(add01 == remove01, "\tTest Add 1 and Remove 1");
	TEST_ASSERT(add02 == remove02, "\tTest Add 2 and Remove 2");
}

//
// Black Box 03
//
// Add value to full buffer
// Remove and test if the added value are in the same order as added.
void TestAddAllAndDequeueIsSameOrder() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t const REPEATS = 3;
	for (int32_t c = 0; c < REPEATS; c++) {
		printf("\tRepeat %d\n", c + 1);
		for(int32_t i = 0; i < BUFFER_SIZE - 1; i++)
			CircularBufferAddElement(&buffer, i);

		for(int32_t i = 0; i < BUFFER_SIZE - 1; i++) {
			int32_t deq = CircularBufferRemoveHead(&buffer);
			TEST_ASSERT(i == deq, "\tTest order, expect %d, got %d", deq, i);
		}
		printf("\n");
	}
}

//
// Black Box 04
//
// Add to full buffer.
// Add another element.
// Check if the last added value failed to be add.
// The return value of the CircularBufferAddElement should return INT32_T.
void TestAddAllCheckForLastFail() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	for(int32_t i = 0; i < BUFFER_SIZE - 1; i++)
		CircularBufferAddElement(&buffer, i);

	int32_t res = CircularBufferAddElement(&buffer, 4);
	TEST_ASSERT(INT32_MIN == res, "\tTest add last, expect %d, got %d ", INT32_MIN, res);
}

//
// Black Box 05
//
// Add to full buffer.
// Remove element and check order.
// Pass if the same order
void TestAddRemoveInOrder() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	for (int32_t i = 0; i < BUFFER_SIZE + 1; i++) {
		CircularBufferAddElement(&buffer, i);
	}
	for (int32_t i = 0; i < BUFFER_SIZE - 1; i++) {
		int32_t res = CircularBufferRemoveHead(&buffer);
		TEST_ASSERT(res == i, "\tTest Add Remove order, expect %d, got %d ", i, res);
	}
}

//
// Black Box 06
//
// Check CircularBufferContains on an empty buffer.
// Should return INT32_T.
void TestContains() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t res = CircularBufferContains(&buffer, 2);
	TEST_ASSERT(res == INT32_MIN, "\tTest contain on empty buffer, expect %d, got %d ", INT32_MIN, res);
}

//
// Black Box 07
//
// Add one element.
// Use CircularBufferContains to check if the added element is there.
// Pass if the function return the same value as added.
void TestAddContains() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t valueToAdd = 2;
	int32_t add = CircularBufferAddElement(&buffer, valueToAdd);
	int32_t contain = CircularBufferContains(&buffer, valueToAdd);

	TEST_ASSERT(add == contain, "\tTest Add and contain, expect %d, got %d ", valueToAdd, contain);
}

//
// Black Box 08
//
// Add 2 element.
// Use CircularBufferContains to check for the second element.
// Pass if function return the same value as the second element.
void TestAddTwoContainSecond() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t valueToAdd1 = 2;
	int32_t valueToAdd2 = 7;
	CircularBufferAddElement(&buffer, valueToAdd1);
	CircularBufferAddElement(&buffer, valueToAdd2);
	int32_t contain = CircularBufferContains(&buffer, valueToAdd2);

	TEST_ASSERT(contain == valueToAdd2, "\tTest Add Two and Contain second value, expect %d, got %d ", valueToAdd2, contain);
}

//
// Black Box 09
//
// Add full buffer with different value.
// Check if the last value exist.
// Pass if exist.
void TestAddBufferSizeDifferentCheckLast() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	int32_t expect = BUFFER_SIZE - 2;
	for (int32_t i = 0; i < BUFFER_SIZE; i++) {
		CircularBufferAddElement(&buffer, i);
	}

	int32_t last = CircularBufferContains(&buffer, expect);
	TEST_ASSERT(last == expect, "\tTest last contain, expect %d, got %d ", expect, last);
}

// White Box InitCircularBuffer()
void TestInitCircularBuffer() {
	int32_t data[BUFFER_SIZE];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, BUFFER_SIZE);

	TEST_ASSERT(buffer.maxLength == BUFFER_SIZE,
			"\tTest CircularBuffer.maxLength, expect %d, got %d ",
			BUFFER_SIZE,
			buffer.maxLength);
	TEST_ASSERT(buffer.head == 0,
			"\tTest CircularBuffer.head, expect %d, got %d ",
			0,
			buffer.head);
	TEST_ASSERT(buffer.tail == 0,
			"\tTest CircularBuffer.tail, expect %d, got %d ",
			0,
			buffer.tail);
}

// White Box CircularBufferAddElement()
void TestCircularBufferAddElement() {
	// BUFFER_SIZE = 4
	int32_t data[4];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, 4);

	CircularBufferAddElement(&buffer, 4);
	TEST_ASSERT(buffer.tail == 1,
			"\tTest Add element, expect tail to be %d, got %d ",
			1, buffer.tail);
	CircularBufferRemoveHead(&buffer);

	CircularBufferAddElement(&buffer, 6);
	TEST_ASSERT(buffer.tail == 2,
			"\tTest Add element, expect tail to be %d, got %d ",
			2, buffer.tail);

	CircularBufferAddElement(&buffer, 8);
	TEST_ASSERT(buffer.head == 1 && buffer.tail == 3,
			"\tTest Add element, expect head %d, got %d, expect tail %d, got %d",
			1, buffer.head, 3, buffer.tail);

	CircularBufferAddElement(&buffer, 9);
	TEST_ASSERT(buffer.head == 1 && buffer.tail == 0,
			"\tTest Add to BUFFER_SIZE - 1 = %d, expect head %d, got %d, expect tail %d, got %d",
			4 - 1,
			1, buffer.head,
			0, buffer.tail);
}

// White Box CircularBufferRemoveValue()
void TestCircularBufferRemoveValue() {
	int32_t data[4];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, 4);

	CircularBufferAddElement(&buffer, 20);
	CircularBufferRemoveValue(&buffer, 20);

	TEST_ASSERT(buffer.head == 0 && buffer.tail == 0,
			"\tTest remove value from buffer contain 1 element, expect head %d, got %d, expect tail %d, got %d ",
			0, buffer.head,
			0, buffer.tail);
	CircularBufferAddElement(&buffer, 22);
	CircularBufferAddElement(&buffer, 20);
	CircularBufferAddElement(&buffer, 22);

	CircularBufferRemoveValue(&buffer, 22);
	TEST_ASSERT(buffer.head == 0 && buffer.tail == 1,
			"\tTest Remove specific value with full buffer, expect head %d, got %d, expect tail %d, got %d ",
			0, buffer.head,
			1, buffer.tail);

	InitCircularBuffer(&buffer, data, 4);  // Clear buffer
	int32_t removed = CircularBufferRemoveValue(&buffer, 20);
	TEST_ASSERT(removed == INT32_MIN,
			"\tTest Remove specific value with empty buffer, expect %d, got %d ",
			INT32_MIN, removed);
}

// White Box CircularBufferRemoveHead()
void TestCircularBufferRemoveHead() {
	int32_t data[4];
	CircularBuffer buffer;
	InitCircularBuffer(&buffer, data, 4);

	CircularBufferAddElement(&buffer, 1);
	CircularBufferRemoveHead(&buffer);

	TEST_ASSERT(buffer.head == 1 && buffer.tail == 1,
			"\tTest RemoveHead with buffer contain 1 element, expect head %d, got %d, expect tail %d, got %d ",
			1, buffer.head,
			1, buffer.tail);

	CircularBufferAddElement(&buffer, 1);
	CircularBufferAddElement(&buffer, 2);
	CircularBufferRemoveHead(&buffer);
	TEST_ASSERT(buffer.head == 2 && buffer.tail == 3,
			"\tTest RemoveHead with buffer contain 2 element, expect head %d, got %d, expect tail %d, got %d ",
			1, buffer.head,
			2, buffer.tail);

	InitCircularBuffer(&buffer, data, 4);  // Clean up
	CircularBufferAddElement(&buffer, 1);
	CircularBufferAddElement(&buffer, 2);
	CircularBufferAddElement(&buffer, 3);

	TEST_ASSERT(buffer.head == 0 && buffer.tail == 3,
			"\tTest RemoveHead with buffer 4 element, expect head %d, got %d, expect tail %d, got %d ",
			0, buffer.head,
			3, buffer.tail);

	InitCircularBuffer(&buffer, data, 4);  // Clean up
	CircularBufferRemoveHead(&buffer);
	TEST_ASSERT(0 == buffer.head && 0 == buffer.tail,
			"\tTest RemoveHead with empty buffer, expect head %d, got %d, expect tail %d, got %d ",
			0, buffer.head,
			0, buffer.tail);
}

void app_main() {
	printf("---- BLACK BOX ----\n");
	TEST_RUN(TestAddAndRemoveElement);
	TEST_RUN(TestAddTwoDifferentValue);
	TEST_RUN(TestAddAllAndDequeueIsSameOrder);
	TEST_RUN(TestAddAllCheckForLastFail);
	TEST_RUN(TestAddRemoveInOrder);
	TEST_RUN(TestContains);
	TEST_RUN(TestAddContains);
	TEST_RUN(TestAddTwoContainSecond);
	TEST_RUN(TestAddBufferSizeDifferentCheckLast);

	printf("\n");
	printf("---- WHITE BOX ----\n");
	TEST_RUN(TestInitCircularBuffer);
	TEST_RUN(TestCircularBufferAddElement);
	TEST_RUN(TestCircularBufferRemoveValue);
	TEST_RUN(TestCircularBufferRemoveHead);

	for(;;) {
		sleep_ms(500);
	}
}

