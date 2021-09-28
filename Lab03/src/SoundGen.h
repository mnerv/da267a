/**
 * @file   SoundGen.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Sound generation with ESP32 DAC.
 * @date   2021-09-28
 *
 * @copyright Copyright (c) 2021
 */
#ifndef SOUND_GEN_H_
#define SOUND_GEN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Play a sound with requested frequency.
 * @param freq Requested frequency to play
 * @return 
 */
int32_t SoundGen_Start(int32_t freq);
void SoundGen_Stop();

#ifdef __cplusplus
}
#endif
#endif

