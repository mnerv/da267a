#include <stdint.h>

#include <driver/gpio.h>
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

extern "C" void app_main();

//
// States:
//      Moving
//      Idle
//      Loading
//      Unloading
//
// Events:
//      Push button on lower level
//      Push external button on upper level
//      Done loading
//      Done unloading
//      Arrive to floor
//
// Transitions:
//      Idle      -> Moving
//      Idle      -> Loading
//      Loading   -> Moving
//      Moving    -> Loading
//      Unloading -> Moving
//
// Datas:
//      Current State
//      Current position
//

void sleep_ms(uint32_t ms) {
    TickType_t delay = ms / portTICK_PERIOD_MS;
    vTaskDelay(delay);
}

auto app_main() -> void {
    while(true) {

    }
}

