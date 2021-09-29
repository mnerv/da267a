#include "Sampler.h"

#define SAMPLE_SIZE 16

volatile uint8_t buffer[SAMPLE_SIZE];

void Sampler_Start(int32_t freq) {
	// TODO: Setup ADC
	// TODO: Start the interrupt for sampling the frequency
}
void Sampler_Stop() {
	// TODO: Stop the timer interrupt
}

float Sampler_GetFreq() {
	// TODO: Compute the sampled values and return it
	return 0.;
}

