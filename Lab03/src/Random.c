/**
 * @file   random.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Random number implementation. This uses esp_system.h to get the
 *         esp_random() function which uses the hardware RNG.
 * @date   2021-09-08
 *
 * @copyright Copyright (c) 2021
 */
#include "Random.h"

#include "esp_system.h"

uint32_t RandRange(uint32_t min, uint32_t max) {
	return (esp_random() % (max - min)) + min;
}

