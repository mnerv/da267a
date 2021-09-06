#include "random.h"

#include "esp_system.h"

int32_t get_random_secs(int32_t min, int32_t max) {
	const uint32_t value = esp_random() % max;
	return value > min ? value : min;
}

