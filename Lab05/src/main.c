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
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "BufferQueue.h"
#include "I2CUtil.h"
#include "MPU6050.h"

#define SDA_PIN 23
#define SCL_PIN 22

#define SAMPLE_PRIORITY  10   // For xTaskCreate
#define COMPUTE_PRIORITY 10   // For xTaskCreate
#define SAMPLE_PERIOD	 166  // ms
#define COMPUTE_PERIOD	 500  // ms

#define BUTTON_PIN            12
#define LED_PIN               13
#define INTR_FLAG_DEFAULT      0
#define PUSH_TIME_US      125000  // Delay between button push in microseconds

#define BUFFER_SIZE   16
// Step-Detection algorithm constant values
#define SD_MIN        0.008  // Minimum Standard Deviation
#define SD_K          1.800  // Standard deviation constant
#define MIN_STEP_TIME 120    // ms
#define STEP_GOAL     10


// Global buffer
BufferQ_t buffer;
float data[BUFFER_SIZE];
int32_t stepCount = 0;
SemaphoreHandle_t xSemaphore = NULL;
uint64_t lastPushTime = -PUSH_TIME_US;

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
		if (!BufferQ_Empty(&buffer)) {
			// Get buffer size
			int32_t size = buffer.entries;
			// Compute SD(Standard Deviation)
			//	   Corrected sample standard deviation
			float mean	= 0.f;
			float sd	= 0.f;
			float* data = (float*)buffer.data;
			for (int32_t i = 0, head = buffer.head; i < size; i++) {
				mean += data[head];
				head  = (head + buffer.max - 1) % buffer.max;
			}
			mean = mean / (float)size;
			for (int32_t i = 0, head = buffer.head; i < size; i++) {
				sd	+= ((data[head] - mean) * (data[head] - mean));
				head = (head + buffer.max - 1) % buffer.max;
			}
			sd = sqrtf(sd / (float)size);
			if (sd < SD_MIN) sd = SD_MIN;  // Check the minimum SD value

			// For keeping track the minimum step time
			uint32_t lastStepTime = -MIN_STEP_TIME;
			uint32_t currStepTime = 0;
			// Count step and empty the queue
			while(!BufferQ_Empty(&buffer)) {
				// Get sample, remove it from queue
				float value   = BufferQ_Dequeue(&buffer);
				currStepTime += SAMPLE_PERIOD;
				// Check: sample > mean + SD_K * sd
				//        and time between last step and this sample > MIN_STEP_TIME
				//        Step found: increase step count
				if (value > mean + SD_K * sd &&
					currStepTime - lastStepTime > MIN_STEP_TIME) {
					stepCount++;
					lastStepTime = currStepTime;
				}
			}
			printf("Step count: %d, SD: %.2f, m: %.2f, m+k*sd: %.2f\n", stepCount, sd, mean, mean + SD_K * sd);
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMPUTE_PERIOD));
	}
}

void on_button(void* arg) {
	uint64_t now = esp_timer_get_time();
	gpio_intr_disable(BUTTON_PIN);
	if ((now - lastPushTime) > PUSH_TIME_US) {
		xSemaphoreGiveFromISR(xSemaphore, NULL);
		lastPushTime = now;
	}
	gpio_intr_enable(BUTTON_PIN);
}

void led_task(void* arg) {
	for (;;) {
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
			if (stepCount >= STEP_GOAL) {
				for (int32_t i = 0; i < 2; i++) {
					gpio_set_level(LED_PIN, 1);
					vTaskDelay(pdMS_TO_TICKS(125));
					gpio_set_level(LED_PIN, 0);
					vTaskDelay(pdMS_TO_TICKS(125));
				}
			}
		}
	}
}

void app_main() {
	// Configure light sleep mode with esp_pm_configure()
	esp_pm_config_esp32_t pconfig = {
		.max_freq_mhz = 80,			// Maximum CPU Frequency
		.min_freq_mhz = 20,			// Minimum CPU Frequency
		.light_sleep_enable = true	// Turns on automatic sleep
	};
	ESP_ERROR_CHECK(esp_pm_configure(&pconfig));
	gpio_config_t config = {
		.pin_bit_mask = (uint64_t)1 << BUTTON_PIN,
		.mode         = GPIO_MODE_INPUT,
		.pull_up_en   = GPIO_PULLUP_ENABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type    = GPIO_INTR_NEGEDGE
	};
	ESP_ERROR_CHECK(gpio_config(&config));
	ESP_ERROR_CHECK(gpio_install_isr_service(INTR_FLAG_DEFAULT));
	ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, on_button, NULL));

	gpio_config_t ledConfig = {
		.pin_bit_mask = (uint64_t)1 << LED_PIN,
		.mode         = GPIO_MODE_OUTPUT,
		.pull_up_en   = GPIO_PULLUP_DISABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type    = GPIO_INTR_DISABLE
	};
	ESP_ERROR_CHECK(gpio_config(&ledConfig));

	xSemaphore = xSemaphoreCreateBinary();

	// Initialise I2C bus and the MPU6050
	I2C_Init(SDA_PIN, SCL_PIN);
	BufferQ_Init(&buffer, data, BUFFER_SIZE);

	xTaskCreate(sample_task,  "SampleTask",  2048, NULL, SAMPLE_PRIORITY,  NULL);
	xTaskCreate(compute_task, "ComputeTask", 2048, NULL, COMPUTE_PRIORITY, NULL);
	xTaskCreate(led_task,     "LedTask",     1024, NULL, 5,                NULL);
}

