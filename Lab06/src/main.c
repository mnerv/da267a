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

#define BUTTON_PIN        12
#define DEBOUNCE_DELAY    125000  // microseconds
#define INTR_FLAG_DEFAULT 0

#define LED_A_PIN 27
#define LED_B_PIN 33
#define LED_C_PIN 15
#define ELEVATOR_SIZE 4

#define TRAVEL_NEED_SIZE   50
#define PUSH_TIME_DELAY_US 250000  // microseconds

typedef struct {
	int32_t origin;
	int32_t dest;
} TravelNeed;

uint64_t lastPushTime = 0;
int32_t  levelCounter = 0;
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
			gpio_set_level(LED_A_PIN, 1);
			gpio_set_level(LED_B_PIN, 0);
			gpio_set_level(LED_C_PIN, 0);
		} else if (level == 1 || level == 3) {
			gpio_set_level(LED_A_PIN, 0);
			gpio_set_level(LED_B_PIN, 1);
			gpio_set_level(LED_C_PIN, 0);
		} else {
			gpio_set_level(LED_A_PIN, 0);
			gpio_set_level(LED_B_PIN, 0);
			gpio_set_level(LED_C_PIN, 1);
		}
		levelCounter++;
	}
	gpio_intr_enable(BUTTON_PIN);
}

void app_main() {
	travelNeeds[0]  = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[1]  = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[2]  = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[3]  = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[4]  = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[5]  = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[6]  = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[7]  = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[8]  = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[9]  = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[10] = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[11] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[12] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[13] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[14] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[15] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[16] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[17] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[18] = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[19] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[20] = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[21] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[22] = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[23] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[24] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[25] = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[26] = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[27] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[28] = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[29] = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[30] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[31] = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[32] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[33] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[34] = (TravelNeed){ .origin = 1, .dest = 2 };
	travelNeeds[35] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[36] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[37] = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[38] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[39] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[40] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[41] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[42] = (TravelNeed){ .origin = 0, .dest = 1 };
	travelNeeds[43] = (TravelNeed){ .origin = 1, .dest = 0 };
	travelNeeds[44] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[45] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[46] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[47] = (TravelNeed){ .origin = 2, .dest = 1 };
	travelNeeds[48] = (TravelNeed){ .origin = 0, .dest = 2 };
	travelNeeds[49] = (TravelNeed){ .origin = 1, .dest = 0 };

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
	config.pin_bit_mask  = (uint64_t) 1 << LED_A_PIN;
	config.pin_bit_mask |= (uint64_t) 1 << LED_B_PIN;
	config.pin_bit_mask |= (uint64_t) 1 << LED_C_PIN;
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

