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

#include "I2CUtil.h"

#define MPU6050_ADDR       0x68
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_WHOAMI     0x75
#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42

#define SDA_PIN 23
#define SCL_PIN 22

void app_main() {
	// TODO: Initialise I2C bus and the MPU6050
	I2C_Init(SDA_PIN, SCL_PIN);
	I2C_Write(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);
	I2C_Write(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 250);

	for (;;) {
		// TODO: Get Acceleration
		// TODO: Print Acceleration data
		uint8_t buffer;
		int16_t tempRaw = 0;
		I2C_Read(MPU6050_ADDR, MPU6050_TEMP_OUT_L, &buffer, 1);
		tempRaw = buffer;
		I2C_Read(MPU6050_ADDR, MPU6050_TEMP_OUT_H, &buffer, 1);
		tempRaw |= ((int16_t)buffer << 8);
		printf("Temp raw: %d\n", tempRaw);
		float temp = ((float)tempRaw) / 340 + 36.53;
		printf("Temp: %.2f C\n", temp);
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

//void app_main() {
//	// TODO: Configure light sleep mode with esp_pm_configure()
//	// TODO: Initialise I2C bus and the MPU6050
//}

