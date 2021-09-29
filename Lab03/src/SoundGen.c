/**
 * @file   SoundGen.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Sound generation with ESP32 DAC implementation.
 *         Plays a sound with requested frequency and stop
 *         the currently playing.
 * @date   2021-09-28
 *
 * @copyright Copyright (c) 2021
 */
#include "SoundGen.h"
#include "driver/gpio.h"
#include "driver/dac.h"

uint32_t SoundGen_Start(uint32_t freq) {
	dac_cw_config_t config = {
		.en_ch  = DAC_CHANNEL_1,
		.scale  = DAC_CW_SCALE_1,
		.phase  = DAC_CW_PHASE_0,
		.freq   = freq,
		.offset = 1
	};
	esp_err_t err = dac_cw_generator_config(&config);
	if (err) return UINT32_MAX;

	err = dac_cw_generator_enable();
	if (err) return UINT32_MAX;
	err = dac_output_enable(DAC_CHANNEL_1);
	if (err) {
		SoundGen_Stop();
		return UINT32_MAX;
	}
	return config.freq;
}
void SoundGen_Stop() {
	dac_cw_generator_disable();
}

