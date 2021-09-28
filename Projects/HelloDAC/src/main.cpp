/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Using ESP32 DAC
 * @date   2021-09-27
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "esp_task_wdt.h"
#include "driver/dac.h"
#include "soc/dac_channel.h"
#include "esp32/rom/ets_sys.h"

extern "C" auto app_main() -> void;

constexpr auto MAX_TIME = 3033UL;

void timer_callback(void *args) {
    uint8_t value = 255;
    auto start    = esp_timer_get_time();
    auto current  = start;
    auto last     = start;
    while(current - start < MAX_TIME) {
        current = esp_timer_get_time();
        if (current - last > MAX_TIME / 255) {
            dac_output_voltage(DAC_GPIO26_CHANNEL, value++);
            last = current;
        }
    }
}

auto app_main() -> void {
    dac_output_enable(DAC_GPIO26_CHANNEL);

    esp_timer_create_args_t config;
    config.name     = "wave_timer";
    config.arg      = nullptr;
    config.callback = timer_callback;

    esp_timer_handle_t timer;
    esp_err_t res = esp_timer_create(&config, &timer);
    ESP_ERROR_CHECK(res);

    res = esp_timer_start_periodic(timer, MAX_TIME);
    ESP_ERROR_CHECK(res);
}

