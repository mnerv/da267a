/**
 * @file   Pins.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Pin initialisation implementation.
 * @date   2021-09-29
 *
 * @copyright Copyright (c) 2021
 */
#include "Pins.h"

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"

#define LED_PIN 13

void InitPins() {
	gpio_config_t config;
	config.pin_bit_mask  = (uint64_t) 1 << LED_PIN;
	config.mode          = GPIO_MODE_OUTPUT;
	config.pull_down_en  = 0;
	config.pull_up_en    = 0;
	gpio_config(&config);
}

void SetLED(uint8_t level) {
	gpio_set_level(LED_PIN, level);
}
