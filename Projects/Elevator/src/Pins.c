#include "Pins.h"

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"

#define PIN_A 12
#define PIN_B 13

#define PIN_C 27

uint8_t InitPins() {
    gpio_config_t config;
    config.pin_bit_mask  = (uint64_t) 1 << PIN_A;
    config.pin_bit_mask |= (uint64_t) 1 << PIN_B;

    config.mode          = GPIO_MODE_DEF_INPUT;
    config.pull_down_en  = 0;
    config.pull_up_en    = 1;
    esp_err_t err = gpio_config(&config);
    return err;
}
uint8_t ReadButtonA() {
    return gpio_get_level(PIN_A);
}
uint8_t ReadButtonB() {
    return gpio_get_level(PIN_B);
}

