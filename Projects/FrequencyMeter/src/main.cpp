/**
 * @file   main.cpp
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Hardware Timer Interrupt
 * @date   2021-09-30
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/gpio.h"
#include "driver/adc.h"
#include "soc/adc_channel.h"
#include "driver/timer.h"
#include "esp_task_wdt.h"

extern "C" auto app_main() -> void;

// This is for suppressing the ERROR on macOS
#ifdef EDITOR_MACOS
#undef  IRAM_ATTR
#define IRAM_ATTR
#endif

constexpr auto TRIGGER = 1312;
int32_t trigCount = 0;
int32_t curSample = 0;
int32_t lasSample = 0;

auto IRAM_ATTR callback(void* args) -> void {
    // Check if interrupt is from TIMER_0
    if (TIMERG0.int_st_timers.t0) {
        TIMERG0.int_clr_timers.t0 = 1;
        lasSample = curSample;
        curSample = adc1_get_raw(ADC1_CHANNEL_0);
        if (lasSample < TRIGGER && curSample > TRIGGER)
            ++trigCount;
        if (lasSample > TRIGGER && curSample < TRIGGER)
            ++trigCount;
        TIMERG0.hw_timer[0].config.alarm_en = TIMER_ALARM_EN;
    }
}

auto app_main() -> void {
    adc_gpio_init(ADC_UNIT_1, adc_channel_t(ADC1_GPIO36_CHANNEL));
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_11db);
    gpio_pullup_en(GPIO_NUM_36);

    timer_config_t config{
        .alarm_en    = TIMER_ALARM_EN,
        .counter_en  = TIMER_START,
        .intr_type   = TIMER_INTR_LEVEL,
        .counter_dir = TIMER_COUNT_UP,
        .auto_reload = TIMER_AUTORELOAD_EN,
        .divider     = 4000,                 // 8MHz / 4000 = 2kHz
    };
    timer_init(TIMER_GROUP_0, TIMER_0, &config);
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 1);

    timer_enable_intr(TIMER_GROUP_0, TIMER_0);
    timer_isr_register(TIMER_GROUP_0, TIMER_0, callback,
                       nullptr, ESP_INTR_FLAG_IRAM, nullptr);
    timer_start(TIMER_GROUP_0, TIMER_0);

    auto startTime = esp_timer_get_time();
    auto endTime   = startTime;

    float freq = 0.f;
    while(true) {
        // Start sampling
        timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
        trigCount = 0;
        startTime = esp_timer_get_time();
        timer_start(TIMER_GROUP_0, TIMER_0);
        vTaskDelay(pdMS_TO_TICKS(250));
        timer_pause(TIMER_GROUP_0, TIMER_0);
        // Stop sampling
        endTime = esp_timer_get_time();

        freq = trigCount * 1000000.f / (2.f * float(endTime - startTime));
        printf("Frequency: %.2f, trigs: %d\n", freq, trigCount);
    }
}

