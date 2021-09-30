/**
 * @file   main.cpp
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Hardware Timer Interrupt
 * @date   2021-09-30
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/timer.h"
#include "esp_task_wdt.h"

extern "C" auto app_main() -> void;

#ifdef EDITOR_MACOS
#undef  IRAM_ATTR
#define IRAM_ATTR
#endif

int64_t counter = 0;

auto IRAM_ATTR callback(void* args) -> void {
    // Check if interrupt is from TIMER_0
    if (TIMERG0.int_st_timers.t0) {
        TIMERG0.int_clr_timers.t0 = 1;
        counter++;
        TIMERG0.hw_timer[0].config.alarm_en = TIMER_ALARM_EN;
    }
}

auto app_main() -> void {
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

    //uint64_t time;
    while(true) {
        //timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &time);
        //printf("%llu\n", time);
        timer_start(TIMER_GROUP_0, TIMER_0);
        vTaskDelay(pdMS_TO_TICKS(250));
        timer_pause(TIMER_GROUP_0, TIMER_0);
        printf("%lld\n", counter);
        counter = 0;
    }
}

