#ifndef LAB01_PINS_H
#define LAB01_PINS_H

#include <stdint.h>

void init_pins();
void set_led_a(uint8_t level);
void set_led_b(uint8_t level);
uint8_t is_button_a_pressed();
uint8_t is_button_b_pressed();

#endif
