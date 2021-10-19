/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Lab06 - State machine elevator
 * @date   2021-10-19
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "esp_task_wdt.h"

#define TRAVEL_NEED_SIZE   50
#define PUSH_TIME_DELAY_US 250000  // microseconds

typedef struct {
	int32_t origin;
	int32_t dest;
} TravelNeed;


uint64_t lastPushTime = 0;
int32_t  travelIndex  = 0;
TravelNeed Travels[TRAVEL_NEED_SIZE];

void OnPush(void* arg) {
	// TODO: Handle when button is pushed
}

void app_main() {
	// TODO: Configure GPIO
	for (;;) {
		// TODO: Simulate elevator
		printf("Hello, World!\n");
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

