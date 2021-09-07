/**
 * @file   pins.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Pin initialisation abstraction interface.
 * @date   2021-09-08
 *
 * @copyright Copyright (c) 2021
 */
#ifndef PINS_H
#define PINS_H

#include <stdint.h>

void init_pins();
void setled_a(uint8_t level);
void setled_b(uint8_t level);
uint8_t isbutton_a_pressed();
uint8_t isbutton_b_pressed();

#endif
