/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  DA267A Lab03 Sound Game with ESP32.
 * @date   2021-09-28
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

void app_main() {
	for (;;) {
		printf("Hello, World!\n");
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

