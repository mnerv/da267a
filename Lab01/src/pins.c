/**
 * @file   pins.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Pin initialisation implementation.
 * @date   2021-09-08
 *
 * @copyright Copyright (c) 2021
 */
#include "pins.h"

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"

#define LED_A 12
#define LED_B 14

#define PIN_A 26
#define PIN_B 27

void init_pins() {
	gpio_config_t config;
	config.pin_bit_mask  = (uint64_t) 1 << PIN_A;
	config.pin_bit_mask |= (uint64_t) 1 << PIN_B;
	config.mode          = GPIO_MODE_DEF_INPUT;
	config.pull_down_en  = 0;
	config.pull_up_en    = 1;
	gpio_config(&config);

	config.pin_bit_mask  = (uint64_t) 1 << LED_A;
	config.pin_bit_mask |= (uint64_t) 1 << LED_B;
	config.mode          = GPIO_MODE_OUTPUT;
	config.pull_down_en  = 0;
	config.pull_up_en    = 0;
	gpio_config(&config);
}

void setled_a(uint8_t level) {
	gpio_set_level(LED_A, level);
}

void setled_b(uint8_t level) {
	gpio_set_level(LED_B, level);
}

uint8_t isbutton_a_pressed() {
	return !(uint8_t)gpio_get_level(PIN_A);
}

uint8_t isbutton_b_pressed() {
	return !(uint8_t)gpio_get_level(PIN_B);
}

