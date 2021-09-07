/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Reaction game implementation with two buttons and two LEDs.
 * @date   2021-09-08
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

#include "pins.h"
#include "random.h"

void wait_ms(uint32_t ms) {
	TickType_t delay = ms / portTICK_PERIOD_MS;
	vTaskDelay(delay);
}

void app_main() {
	init_pins();

	for (;;) {
		// TODO: Signal for game to start

		// TODO: Switch both LEDs off

		// TODO: Get random duration between 3 and 5 seconds

		// TODO: Wait with random duration

		// TODO: Switch both LEDs ON

		uint8_t winner = 0;

		while (!winner) {
			// TODO: Check if either button A or B are presseed

			// TODO: If any is pressed, set winner to 1 for A and 2 for B
		}

		// TODO: If A wins, flash LED A and switch off B
		// TODO: If B wins, flash LED A and switch off A

		// TODO: Switch off both A and B and wiat for some time to restart the game
	}

}

//void app_main() {
//	init_pins();
//
//	for (;;) {
//		int32_t value = getrandom_secs(100, 500);
//		printf("Random value: %d\n", value);
//
//		setled_a(1);
//		setled_b(0);
//		wait_ms(value);
//
//		setled_a(0);
//		setled_b(1);
//		wait_ms(value);
//	}
//}

//void app_main() {
//	init_pins();
//
//	for (;;) {
//		if (isbutton_a_pressed()) {
//			setled_a(1);
//			setled_b(0);
//		} else if (isbutton_b_pressed()) {
//			setled_a(0);
//			setled_b(1);
//		} else {
//			setled_a(1);
//			setled_b(0);
//			wait_ms(500);
//
//			setled_a(0);
//			setled_b(1);
//			wait_ms(500);
//		}
//	}
//}

