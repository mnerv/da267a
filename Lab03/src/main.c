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
#include "Random.h"
#include "Pins.h"

#define SAMPLING_FREQ 4000

void BlinkLED(int32_t ms, int32_t times) {
	for (int32_t i = 0; i < times; i++) {
		SetLED(1);
		vTaskDelay(pdMS_TO_TICKS(ms));
		SetLED(0);
		vTaskDelay(pdMS_TO_TICKS(ms));
	}
}

float abs_float(float a) {
	return a > 0 ? a : -a;
}

void app_main() {
	InitPins();

	for (;;) {
		printf("Game Start!!!\n");

		BlinkLED(50, 20);
		int32_t randFreq = RandRange(200, 1000);
		int32_t actFreq  = SoundGen_Start(randFreq);

		vTaskDelay(pdMS_TO_TICKS(3000));

		SoundGen_Stop();

		printf("Make the tone!!!\n");
		Sampler_Start(SAMPLING_FREQ);
		vTaskDelay(pdMS_TO_TICKS(1000));
		Sampler_Stop();

		float freq = Sampler_GetFreq();
		printf("Player: %.2f, Actual: %d\n", freq, actFreq);
		if (abs_float(freq - (float)actFreq) < 50) {
			printf("\tPlayer wins!\n");
			BlinkLED(100, 20);
		} else {
			printf("\tPlayer loses!\n");
			BlinkLED(1000, 2);
		}
	}
}

