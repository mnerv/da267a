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

/*!
 * Get random value between min and max,
 * where min >= 0 and max <= UINT32_MAX and max > min.
 *
 * @param min Minimum value
 * @param max Maximum value
 *
 * @return random value between min and max.
 */
uint32_t rand_range(uint32_t min, uint32_t max);

#endif
