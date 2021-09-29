/**
 * @file   Sampler.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Sample sound from ESP32 ADC
 * @date   2021-09-28
 *
 * @copyright Copyright (c) 2021
 */
#ifndef SAMPLER_H_
#define SAMPLER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Start sampling given frequency.
 * @param freq Sampling frequency.
 */
void Sampler_Start(int32_t freq);
void Sampler_Stop();
/**
 * @brief  Compute the sampled frequency.
 * @return Computed frequency.
 */
float Sampler_GetFreq();

#ifdef __cplusplus
}
#endif
#endif

