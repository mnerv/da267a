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
#define SAMPLE_PERIOD    166  // ms
#define COMPUTE_PERIOD   500  // ms

#define BUFFER_SIZE    16
// Step-Detection algorithm constant values
#define SD_MIN         0.270  // Minimum Standard Deviation
#define SD_K           0.600  // Standard deviation constant

// Global buffer
BufferQ_t buffer;
float data[BUFFER_SIZE];
int32_t stepCount = 0;

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
		if (BufferQ_Full(&buffer)) {
			// Get buffer size
			int32_t size = buffer.entries;
			// Compute SD(Standard Deviation)
			float sum    = 0.f;
			int32_t head = buffer.head;
			for (int32_t i = 0; i < size; i++) {
				float* data = (float*)buffer.data;
				sum += data[head];
				head = (head + buffer.max - 1) % buffer.max;
			}
			float mean = sum / (float)size;
			float sd   = sqrtf(mean / (float)size);
			if (sd < SD_MIN) sd = SD_MIN;

			// Count step and empty the queue
			while(!BufferQ_Empty(&buffer)) {
				// Get sample, remove it from queue
				float value = BufferQ_Dequeue(&buffer);
				// Check: sample > mean + SD_K * sd
				//        and time between last step and this sample > MIN_STEP_TIME
				//        Step found: increase step count
				if (value > mean + SD_K * sd) {
					stepCount++;
				}
			}
		}
		printf("Step count: %d\n", stepCount);
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

