/**
 * @file   MPU6050.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  MPU6050 I2C driver
 * @date   2021-10-12
 *
 * @copyright Copyright (c) 2021
 */
#include "MPU6050.h"
#include "I2CUtil.h"

#define AFS_SEL0_LSB 16384.0f  //    2 g
#define AFS_SEL1_LSB  8192.0f  //    4 g
#define AFS_SEL2_LSB  4096.0f  //    8 g
#define AFS_SEL3_LSB  2048.0f  //   16 g
#define FS_SEL0_LSB    131.0f  //  250 °/s
#define FS_SEL1_LSB     65.5f  //  500 °/s
#define FS_SEL2_LSB     32.8f  // 1000 °/s
#define FS_SEL3_LSB     16.4f  // 2000 °/s

float accLSB  = AFS_SEL0_LSB;
float gyroLSB = FS_SEL0_LSB;
uint8_t localbuffer;

void MPU6050_Config(uint8_t regster, uint8_t data) {
	I2C_Write(MPU6050_ADDR, regster, data);
}

void MPU6050_AccConfig(uint8_t flag) {
	uint8_t accConfig = (flag & 0b00011000) >> 3;
	switch(accConfig) {
		case 0:
			accLSB = AFS_SEL0_LSB;
			break;
		case 1:
			accLSB = AFS_SEL1_LSB;
			break;
		case 2:
			accLSB = AFS_SEL2_LSB;
			break;
		case 3:
			accLSB = AFS_SEL3_LSB;
			break;
	}
	I2C_Write(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, flag);
}

void MPU6050_GyroConfig(uint8_t flag) {
}

void MPU6050_Update(MPU6050* mpu6050) {
	I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_XOUT_L, &localbuffer, 1);
	mpu6050->raw_accx  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, &localbuffer, 1);
	mpu6050->raw_accx |= (int16_t)localbuffer << 8;
	I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_YOUT_L, &localbuffer, 1);
	mpu6050->raw_accy  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_YOUT_H, &localbuffer, 1);
	mpu6050->raw_accy |= (int16_t)localbuffer << 8;
	I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_L, &localbuffer, 1);
	mpu6050->raw_accz  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_H, &localbuffer, 1);
	mpu6050->raw_accz |= (int16_t)localbuffer << 8;

	I2C_Read(MPU6050_ADDR, MPU6050_GYRO_XOUT_L, &localbuffer, 1);
	mpu6050->raw_gyrox  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_GYRO_XOUT_H, &localbuffer, 1);
	mpu6050->raw_gyrox |= (int16_t)localbuffer << 8;
	I2C_Read(MPU6050_ADDR, MPU6050_GYRO_YOUT_L, &localbuffer, 1);
	mpu6050->raw_gyroy  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_GYRO_YOUT_H, &localbuffer, 1);
	mpu6050->raw_gyroy |= (int16_t)localbuffer << 8;
	I2C_Read(MPU6050_ADDR, MPU6050_GYRO_ZOUT_L, &localbuffer, 1);
	mpu6050->raw_gyroz  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_GYRO_ZOUT_H, &localbuffer, 1);
	mpu6050->raw_gyroz |= (int16_t)localbuffer << 8;

	I2C_Read(MPU6050_ADDR, MPU6050_TEMP_OUT_L, &localbuffer, 1);
	mpu6050->raw_temp  = localbuffer;
	I2C_Read(MPU6050_ADDR, MPU6050_TEMP_OUT_H, &localbuffer, 1);
	mpu6050->raw_temp |= (int16_t)localbuffer << 8;

	mpu6050->accx  = (float)mpu6050->raw_accx  / accLSB;
	mpu6050->accy  = (float)mpu6050->raw_accy  / accLSB;
	mpu6050->accz  = (float)mpu6050->raw_accz  / accLSB;
	mpu6050->gyrox = (float)mpu6050->raw_gyrox / gyroLSB;
	mpu6050->gyroy = (float)mpu6050->raw_gyroy / gyroLSB;
	mpu6050->gyroz = (float)mpu6050->raw_gyroz / gyroLSB;
}

