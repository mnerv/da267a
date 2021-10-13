#include "I2CUtil.h"
#include "driver/i2c.h"

#define RATE 1000  // ms

void I2C_Init(int32_t sda, int32_t scl) {
	i2c_config_t config = {
		.mode             = I2C_MODE_MASTER,
		.sda_io_num       = sda,
		.scl_io_num       = scl,
		.sda_pullup_en    = GPIO_PULLUP_ENABLE,
		.scl_pullup_en    = GPIO_PULLUP_ENABLE,
		.master.clk_speed = 100000  // 100kHz
	};
	esp_err_t err = i2c_param_config(I2C_NUM_0, &config);
	ESP_ERROR_CHECK(err);
	err = i2c_driver_install(I2C_NUM_0, config.mode, 0, 0, 0);
	ESP_ERROR_CHECK(err);
}

void I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	esp_err_t err = i2c_master_start(cmd);      // Start command
	ESP_ERROR_CHECK(err);
	err = i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 1);
	ESP_ERROR_CHECK(err);
	err = i2c_master_write_byte(cmd, reg, 1);   // Write to register
	ESP_ERROR_CHECK(err);
	err = i2c_master_write_byte(cmd, data, 1);  // Write data
	ESP_ERROR_CHECK(err);
	err = i2c_master_stop(cmd);                // End command
	ESP_ERROR_CHECK(err);

	err = i2c_master_cmd_begin(I2C_NUM_0, cmd, RATE / portTICK_RATE_MS);
	ESP_ERROR_CHECK(err);
	i2c_cmd_link_delete(cmd);
}

void I2C_Read(uint8_t address, uint8_t reg, uint8_t* buffer, int32_t len) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	esp_err_t err = i2c_master_start(cmd);
	ESP_ERROR_CHECK(err);
	err = i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 1);
	ESP_ERROR_CHECK(err);
	err = i2c_master_write_byte(cmd, reg, 1);
	ESP_ERROR_CHECK(err);
	err = i2c_master_stop(cmd);
	ESP_ERROR_CHECK(err);
	err = i2c_master_cmd_begin(I2C_NUM_0, cmd, RATE / portTICK_RATE_MS);
	ESP_ERROR_CHECK(err);
	i2c_cmd_link_delete(cmd);

	cmd = i2c_cmd_link_create();
	err = i2c_master_start(cmd);
	ESP_ERROR_CHECK(err);
	err = i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, 1);
	ESP_ERROR_CHECK(err);
	err = i2c_master_read(cmd, buffer, len, I2C_MASTER_NACK);
	ESP_ERROR_CHECK(err);
	err = i2c_master_stop(cmd);
	ESP_ERROR_CHECK(err);
	err = i2c_master_cmd_begin(I2C_NUM_0, cmd, RATE / portTICK_RATE_MS);
	ESP_ERROR_CHECK(err);
	i2c_cmd_link_delete(cmd);
}

