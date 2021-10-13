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

void MPU6050_Init(uint8_t mpu6050Config);

#ifdef __cplusplus
}
#endif
#endif

