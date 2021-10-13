/**
 * @file   I2CUTil.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  I2C Utility
 * @date   2021-10-12
 *
 * @copyright Copyright (c) 2021
 */
#ifndef I2CUTIL_H_
#define I2CUTIL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialise the I2C bus
 */
void I2C_Init(int32_t sda, int32_t scl);
void I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void I2C_Read(uint8_t address, uint8_t reg, uint8_t* buffer, int32_t len);

#ifdef __cplusplus
}
#endif
#endif

