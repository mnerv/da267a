/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Generating PWM signal
 * @date   2021-09-27
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include <driver/gpio.h>
#include <driver/ledc.h>
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

#include "Hello.h"
extern "C" auto app_main() -> void;

auto app_main() -> void {
    ledc_timer_config_t timer_config{
        .speed_mode      = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num       = LEDC_TIMER_0,
        .freq_hz         = 5000,
        .clk_cfg         = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_config);

    ledc_channel_config_t channel_config{
        .gpio_num   = GPIO_NUM_13,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = 512,
        .hpoint     = 0,
    };
    ledc_channel_config(&channel_config);

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

