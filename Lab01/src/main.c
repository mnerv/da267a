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

#define PLAYER_A       1
#define PLAYER_B       2
#define UNKNOWN_PLAYER 0

void wait_ms(uint32_t ms) {
	TickType_t delay = ms / portTICK_PERIOD_MS;
	vTaskDelay(delay);
}

void start_animation() {
	for (int32_t i = 0; i < 3; i++) {
		setled_a(1);
		setled_b(0);
		wait_ms(500);
		setled_a(0);
		setled_b(1);
		wait_ms(500);
	}
	for (int32_t i = 0; i < 6; i++) {
		setled_a(1);
		setled_b(1);
		wait_ms(250);
		setled_a(0);
		setled_b(0);
		wait_ms(250);
	}
}

void winner_animation(uint8_t winner) {
	if (winner == UNKNOWN_PLAYER) return;
	for (int32_t i = 0; i < 5; i++) {
		if (winner == PLAYER_A) {
			setled_a(1);
			setled_b(0);
		} else if (winner == PLAYER_B) {
			setled_a(0);
			setled_b(1);
		}
		wait_ms(125);
		setled_a(0);
		setled_b(0);
		wait_ms(125);
	}
}

void app_main() {
	init_pins();

	for (;;) {
		// Signal for game to start
		start_animation();

		// Switch both LEDs off
		setled_a(0);
		setled_b(0);

		// Get random duration between 3 and 5 seconds
		uint32_t wait_dur = rand_range(3000, 5000);

		// Wait with random duration
		wait_ms(wait_dur);

		// Switch both LEDs ON
		setled_a(1);
		setled_b(1);

		uint8_t winner = 0;

		while (!winner) {
			// Check if either button A or B are presseed
			// If any is pressed, set winner to 1 for A and 2 for B
			if (isbutton_a_pressed()) {
				winner = PLAYER_A;
				break;
			}
			if (isbutton_b_pressed()) {
				winner = PLAYER_B;
				break;
			}
		}

		// Winner animation
		winner_animation(winner);
		// Switch off both A and B and wiat for some time to restart the game
		setled_a(0);
		setled_b(0);
		wait_ms(2000);
	}

}

