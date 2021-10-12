/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  DA267A Lab05
 * @date   2021-10-12
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "esp_task_wdt.h"

/**
 * @brief Initialise the I2C bus
 */
void InitI2C(int32_t sda, int32_t sdl) {
}

void WriteI2C(uint8_t address, uint8_t reg, uint8_t data) {
}

void ReadI2C(uint8_t address, uint8_t reg, uint8_t* buffer, int32_t len) {
}

void app_main() {
	// TODO: Initialise I2C bus and the MPU6050
	for (;;) {
		// TODO: Get Acceleration
		// TODO: Print Acceleration data
		printf("Hello, World!\n");
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

//void app_main() {
//	// TODO: Configure light sleep mode with esp_pm_configure()
//	// TODO: Initialise I2C bus and the MPU6050
//}

