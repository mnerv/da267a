#include "Sampler.h"

#include "driver/gpio.h"
#include "driver/adc.h"
#include "soc/adc_channel.h"
#include "esp_timer.h"

#define SAMPLE_SIZE 16

volatile uint16_t buffer[SAMPLE_SIZE];
esp_timer_handle_t timer_handler;

void callback(void* args) {
	//for (int32_t i = 0; i < SAMPLE_SIZE; i++) {
	//	int32_t adc = adc1_get_raw(ADC1_CHANNEL_0);
	//	buffer[i] = adc;
	//}
	int32_t adc = adc1_get_raw(ADC1_CHANNEL_0);
	printf("%d\n", adc);
}

void Sampler_Start(int32_t freq) {
	// Setup ADC
	adc_power_on();
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
	int64_t const T = (int64_t)(1000000. / ((double)freq * 2.));  // T = 1 / f, in microseconds
	ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, T));
}
void Sampler_Stop() {
	esp_timer_stop(timer_handler);
}

float Sampler_GetFreq() {
	// TODO: Compute the sampled values and return it
	return 0.;
}

