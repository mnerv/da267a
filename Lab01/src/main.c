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
//		int32_t value = get_random_secs(100, 500);
//		printf("Random value: %d\n", value);
//
//		set_led_a(1);
//		set_led_b(0);
//		wait_ms(value);
//
//		set_led_a(0);
//		set_led_b(1);
//		wait_ms(value);
//	}
//}

//void app_main() {
//	init_pins();
//
//	for (;;) {
//		if (is_button_a_pressed()) {
//			set_led_a(1);
//			set_led_b(0);
//		} else if (is_button_b_pressed()) {
//			set_led_a(0);
//			set_led_b(1);
//		} else {
//			set_led_a(1);
//			set_led_b(0);
//			wait_ms(500);
//
//			set_led_a(0);
//			set_led_b(1);
//			wait_ms(500);
//		}
//	}
//}

