/**
 * @file   Sampler.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Sample sound from ESP32 ADC with high resolution
 *         timer interrupt callback.
 * @date   2021-09-28
 *
 * @copyright Copyright (c) 2021
 */
#include "Sampler.h"

#include "driver/gpio.h"
#include "driver/adc.h"
#include "soc/adc_channel.h"
#include "esp_timer.h"

// Mid Trigger: 1024
#define TRIGGER     1024
#define SAMPLE_SIZE 16

esp_timer_handle_t timer_handler;
int32_t counter      = 0;
int32_t lastSample   = 0;
int32_t currSample   = 0;
int64_t startTime    = 0;
int64_t endTime      = 0;

void callback(void* args) {
	lastSample = currSample;
	currSample = adc1_get_raw(ADC1_CHANNEL_0);
	if (lastSample < TRIGGER && currSample > TRIGGER)
		counter++;
}

void Sampler_Start(int32_t freq) {
	counter = 0;

	// Setup ADC
	adc_gpio_init(ADC_UNIT_1, (adc_channel_t)ADC1_GPIO36_CHANNEL);
	adc1_config_width(ADC_WIDTH_12Bit);
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
	gpio_pullup_en(GPIO_NUM_36);

	// Start the interrupt for sampling the frequency
	esp_timer_create_args_t periodic_timer_args = {
		.callback        = callback,
		.arg             = NULL,
		.dispatch_method = ESP_TIMER_TASK,
		.name            = "sampler"
	};
	ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &timer_handler));
	int64_t const T = (int64_t)(1000000.f / ((float)freq));  // T = 1 / f, in microseconds

	ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, T));
	startTime = esp_timer_get_time();
}
void Sampler_Stop() {
	esp_timer_stop(timer_handler);
	endTime = esp_timer_get_time();
}
float Sampler_GetFreq() {
	float freq = (float)counter / ((float)(endTime - startTime) / 1000000.);
	return freq;
}

