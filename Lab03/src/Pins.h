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

void InitPins();
void SetLED(uint8_t level);

#endif
