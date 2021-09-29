#include "Sampler.h"

#include "driver/gpio.h"
#include "driver/adc.h"
#include "soc/adc_channel.h"
#include "esp_timer.h"

#define SAMPLE_SIZE 16

volatile uint8_t buffer[SAMPLE_SIZE];
esp_timer_handle_t timer_handler;

void callback(void* args) {
	int32_t adc = adc1_get_raw(ADC1_CHANNEL_0);
	printf("CALLBACK YO!\n");
	// TODO: Sample the ADC here
}

void Sampler_Start(int32_t freq) {
	adc_power_on();
	adc_gpio_init(ADC_UNIT_1, (adc_channel_t)ADC1_GPIO36_CHANNEL);
	adc1_config_width(ADC_WIDTH_12Bit);
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
	gpio_pullup_en(GPIO_NUM_36);

	esp_timer_create_args_t periodic_timer_args = {
		.callback        = callback,
		.arg             = NULL,
		.dispatch_method = ESP_TIMER_TASK,
		.name            = "sampler"
    };
	ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &timer_handler));
	ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, 500000));


	// TODO: Setup ADC
	// TODO: Start the interrupt for sampling the frequency

}
void Sampler_Stop() {
	esp_timer_stop(timer_handler);
}

float Sampler_GetFreq() {
	// TODO: Compute the sampled values and return it
	return 0.;
}

