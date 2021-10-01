/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Reading and sample the microphone signal.
 * @date   2021-09-23
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include <driver/gpio.h>
#include <driver/adc.h>
#include <soc/adc_channel.h>
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

#include "Hello.h"
extern "C" auto app_main() -> void;

constexpr auto SAMPLE_SIZE = 256;

auto app_main() -> void {
    adc_gpio_init(ADC_UNIT_1, static_cast<adc_channel_t>(ADC1_GPIO36_CHANNEL));
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    gpio_pullup_en(GPIO_NUM_36);

    int32_t samples[SAMPLE_SIZE];

    while (true) {
        for (int32_t i = 0; i < SAMPLE_SIZE; i++) {
            int32_t adc = adc1_get_raw(ADC1_CHANNEL_0);
            samples[i] = adc;
        }
        for (int32_t i = 0; i < SAMPLE_SIZE; i++) {
            printf("%d\n", samples[i]);
        }
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}

