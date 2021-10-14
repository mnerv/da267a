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

#define AFS_SEL0_LSB 16384.f  //  2g
#define AFS_SEL1_LSB  8192.f  //  4g
#define AFS_SEL2_LSB  4096.f  //  8g
#define AFS_SEL3_LSB  2048.f  // 16g

float selected_lsb = AFS_SEL0_LSB;
uint8_t localbuffer;

void MPU6050_Config(uint8_t regster, uint8_t data) {
	I2C_Write(MPU6050_ADDR, regster, data);
}

void MPU6050_AccConfig(uint8_t flag) {
	uint8_t accConfig = (flag & 0b00011000) >> 3;
	switch(accConfig) {
		case 0:
			selected_lsb = AFS_SEL0_LSB;
			break;
		case 1:
			selected_lsb = AFS_SEL1_LSB;
			break;
		case 2:
			selected_lsb = AFS_SEL2_LSB;
			break;
		case 3:
			selected_lsb = AFS_SEL3_LSB;
			break;
	}
	I2C_Write(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, flag);
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

	mpu6050->accx = (float)mpu6050->raw_accx / selected_lsb;
	mpu6050->accy = (float)mpu6050->raw_accy / selected_lsb;
	mpu6050->accz = (float)mpu6050->raw_accz / selected_lsb;

}

