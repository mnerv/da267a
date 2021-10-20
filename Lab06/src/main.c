/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Lab06 - State machine elevator
 * @date   2021-10-19
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/gpio.h"
#include "esp_task_wdt.h"

#define BUTTON_PIN         12
#define DEBOUNCE_DELAY     125000  // microseconds
#define INTR_FLAG_DEFAULT  0

#define LED_A 27
#define LED_B 33
#define LED_C 15
#define ELEVATOR_SIZE 4

#define TRAVEL_NEED_SIZE   50
#define PUSH_TIME_DELAY_US 250000  // microseconds

typedef struct {
	int32_t origin;
	int32_t dest;
} TravelNeed;


uint64_t lastPushTime = 0;
int32_t  levelCounter  = 0;
TravelNeed travelNeeds[TRAVEL_NEED_SIZE];

void on_push(void* arg) {
	uint64_t now = esp_timer_get_time();
	gpio_intr_disable(BUTTON_PIN);
	if ((now - lastPushTime) > DEBOUNCE_DELAY) {
		// TODO: Handle when button is pushed
		lastPushTime = now;

		TravelNeed travel = travelNeeds[levelCounter];
		uint32_t level    = levelCounter % ELEVATOR_SIZE;

		if (level == 0) {
			gpio_set_level(LED_A, 1);
			gpio_set_level(LED_B, 0);
			gpio_set_level(LED_C, 0);
		} else if (level == 1 || level == 3) {
			gpio_set_level(LED_A, 0);
			gpio_set_level(LED_B, 1);
			gpio_set_level(LED_C, 0);
		} else {
			gpio_set_level(LED_A, 0);
			gpio_set_level(LED_B, 0);
			gpio_set_level(LED_C, 1);
		}
		levelCounter++;
	}
	gpio_intr_enable(BUTTON_PIN);
}

void app_main() {
	gpio_config_t config = {
		.pin_bit_mask = (uint64_t)1 << BUTTON_PIN,
		.mode         = GPIO_MODE_INPUT,
		.pull_up_en   = GPIO_PULLUP_ENABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type    = GPIO_INTR_NEGEDGE
	};
	ESP_ERROR_CHECK(gpio_config(&config));
	ESP_ERROR_CHECK(gpio_install_isr_service(INTR_FLAG_DEFAULT));
	ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, on_push, NULL));
	config.pin_bit_mask  = (uint64_t) 1 << LED_A;
	config.pin_bit_mask |= (uint64_t) 1 << LED_B;
	config.pin_bit_mask |= (uint64_t) 1 << LED_C;
	config.mode          = GPIO_MODE_OUTPUT;
	config.pull_up_en    = GPIO_PULLUP_DISABLE;
	config.pull_down_en  = GPIO_PULLDOWN_DISABLE;
	config.intr_type     = GPIO_INTR_DISABLE;
	ESP_ERROR_CHECK(gpio_config(&config));

	for (;;) {
		// TODO: Simulate elevator
		printf("Hello, World!\n");
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

