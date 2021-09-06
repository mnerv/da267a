#include <stdint.h>

#include <driver/gpio.h>
#include <esp32/rom/ets_sys.h>
#include <esp_task_wdt.h>

#include "pins.h"

void wait_ms(uint32_t ms) {
	TickType_t delay = ms / portTICK_PERIOD_MS;
}

void app_main() {

}

