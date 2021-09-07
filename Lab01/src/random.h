/**
 * @file   random.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Random number interface.
 * @date   2021-09-08
 *
 * @copyright Copyright (c) 2021
 */
#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

uint32_t rand_range(uint32_t min, uint32_t max);
uint32_t rand_max(uint32_t max);

#endif
