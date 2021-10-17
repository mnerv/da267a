/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  DA267A Lab05 - Step counter with Light Sleep on ESP32
 * @date   2021-10-12
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>
#include <math.h>

#include "driver/gpio.h"
#include "esp_task_wdt.h"
#include "esp_pm.h"

#include "BufferQueue.h"
#include "I2CUtil.h"
#include "MPU6050.h"

#define SDA_PIN 23
#define SCL_PIN 22

#define SAMPLE_PRIORITY  10
#define COMPUTE_PRIORITY 10
#define SAMPLE_PERIOD    33  // ms
#define COMPUTE_PERIOD   100  // ms

#define BUFFER_SIZE    16
// Step-Detection algorithm constant values
#define MIN_SD         0    // Minimum Standard Deviation
#define SD_K           0    // Standard deviation constant
#define MIN_STEP_TIME  0    // Minimum time between each step

// Global buffer
BufferQ_t buffer;
float data[BUFFER_SIZE];

void sample_task(void* args) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	MPU6050 mpu;
	MPU6050_Config(MPU6050_PWR_MGMT_1, 0x00);
	MPU6050_Config(MPU6050_SMPLRT_DIV, 250);
	MPU6050_AccConfig(0x00);

	for(;;) {
		MPU6050_Update(&mpu);  // Get accelerations
		float mag = sqrtf(mpu.accx * mpu.accx +
		                  mpu.accy * mpu.accy +
		                  mpu.accz * mpu.accz);  // Compute magnitude
		// Add to buffer
		BufferQ_Enqueue(&buffer, mag);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SAMPLE_PERIOD));
	}
}

void compute_task(void* args) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;) {
		// TODO: Get buffer size
		// TODO: Compute SD(Standard Deviation)

		// TODO: Count step and empty the queue
		// TODO: Get sample, remove it from queue
		// TODO: Check: sample > mean, mean + SD_K * sd
		//              and time between last step and this sample > MIN_STEP_TIME
		//              Step found: increase step count
		int32_t totalSample = 0;
		while(!BufferQ_Empty(&buffer)) {
			printf("%.2f\n", BufferQ_Dequeue(&buffer));
			totalSample++;
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMPUTE_PERIOD));
	}
}

void app_main() {
	// Configure light sleep mode with esp_pm_configure()
	esp_pm_config_esp32_t pconfig = {
		.max_freq_mhz = 80,         // Maximum CPU Frequency
		.min_freq_mhz = 20,         // Minimum CPU Frequency
		.light_sleep_enable = true  // Turns on automatic sleep
	};
	esp_err_t err = esp_pm_configure(&pconfig);
	ESP_ERROR_CHECK(err);

	// Initialise I2C bus and the MPU6050
	I2C_Init(SDA_PIN, SCL_PIN);
	BufferQ_Init(&buffer, data, BUFFER_SIZE);

	xTaskCreate(sample_task,  "SampleTask",  2048, NULL, SAMPLE_PRIORITY,  NULL);
	xTaskCreate(compute_task, "ComputeTask", 2048, NULL, COMPUTE_PRIORITY, NULL);
}

