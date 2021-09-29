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

#include "SoundGen.h"
#include "Sampler.h"

void app_main() {
	uint32_t freq = 130;

	int32_t current = esp_timer_get_time();
	int32_t last    = current;

	for (;;) {
		current = esp_timer_get_time();
		if (current - last > 500) {
			SoundGen_Start(freq);
			freq += 10;

			if (freq > 15000)
				freq = 130;
			last = current;
		}

		//printf("Freq: %d\n", freq);
		//vTaskDelay(pdMS_TO_TICKS(250));
		//SoundGen_Stop();
		//vTaskDelay(pdMS_TO_TICKS(250));
	}
}

//void app_main() {
//	for (;;) {
//		printf("Start sampling...\n");
//		Sampler_Start(6000);
//		vTaskDelay(pdMS_TO_TICKS(1000));
//
//		Sampler_Stop();
//		printf("Stop  sampling...\n");
//
//		float freq = Sampler_GetFreq();
//		printf("Freq: %.2f\n", freq);
//	}
//}

