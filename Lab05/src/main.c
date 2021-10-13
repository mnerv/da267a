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

#define MPU6050_ADDR         0x68
#define MPU6050_PWR_MGMT_1   0x6B  // Power Management 1
#define MPU6050_SMPLRT_DIV   0x19  // Sample Rate Divider
#define MPU6050_GYRO_CONFIG  0x1B  // Gyroscope Configuration
#define MPU6050_ACCEL_CONFIG 0x1C  // Accelerometer Configuration
#define MPU6050_FIFO_EN      0x23  // FIFO Enable
#define MPU6050_INT_PIN_CFG  0x37  // INT Pin / Bypass Enable Configuration
#define MPU6050_INT_ENABLE   0x38  // Interrupt Enable
#define MPU6050_INT_STATUS   0x3A  // Interrupt Status

#define MPU6050_ACCEL_XOUT_H 0x3B  // Accelerometer Measurement X-axis register
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D  // Accelerometer Measurement Y-axis register
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F  // Accelerometer Measurement Z-axis register
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H   0x41
#define MPU6050_TEMP_OUT_L   0x42
#define MPU6050_GYRO_XOUT_H  0x43
#define MPU6050_GYRO_XOUT_L  0x44
#define MPU6050_GYRO_YOUT_H  0x45
#define MPU6050_GYRO_YOUT_L  0x46
#define MPU6050_GYRO_ZOUT_H  0x47
#define MPU6050_GYRO_ZOUT_L  0x48

#define MPU6050_FIFO_COUNT_H 0x72  // FIFO Count Registers
#define MPU6050_FIFO_COUNT_L 0x73

#define MPU6050_WHO_AM_I     0x75  // Who Am I

#define SDA_PIN 23
#define SCL_PIN 22

void app_main() {
	// Initialise I2C bus and the MPU6050
	I2C_Init(SDA_PIN, SCL_PIN);
	I2C_Write(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);
	I2C_Write(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 250);

	I2C_Write(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 0b00000000);

	for (;;) {
		uint8_t buffer;
		// Get Acceleration
		int16_t accx = 0, accy = 0, accz = 0;
		I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_XOUT_L, &buffer, 1);
		accx  = buffer;
		I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, &buffer, 1);
		accx |= ((int16_t)buffer << 8);

		I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_YOUT_L, &buffer, 1);
		accy  = buffer;
		I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_YOUT_H, &buffer, 1);
		accy |= ((int16_t)buffer << 8);

		I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_L, &buffer, 1);
		accz  = buffer;
		I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_H, &buffer, 1);
		accz |= ((int16_t)buffer << 8);

		// Print Acceleration data
		printf("acc: %.2f, %.2f, %.2f\n", (float)accx / 16384., (float)accy / 16384., (float)accz / 16384.);

		vTaskDelay(pdMS_TO_TICKS(15));
	}
}

//void app_main() {
//	// TODO: Configure light sleep mode with esp_pm_configure()
//	// TODO: Initialise I2C bus and the MPU6050
//}

