/**
 * @file   MPU6050.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  MPU6050 I2C driver
 * @date   2021-10-12
 *
 * @copyright Copyright (c) 2021
 */
#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct {
	int16_t raw_accx;
	int16_t raw_accy;
	int16_t raw_accz;

	int16_t raw_gyrox;
	int16_t raw_gyroy;
	int16_t raw_gyroz;

	int16_t raw_temp;

	float accx, accy, accz;
	float gyrox, gyroy, gyroz;
	float temp;
} MPU6050;

void MPU6050_Config(uint8_t regster, uint8_t data);
void MPU6050_AccConfig(uint8_t flag);
void MPU6050_GyroConfig(uint8_t flag);
void MPU6050_Update(MPU6050* mpu6050);

#ifdef __cplusplus
}
#endif
#endif

