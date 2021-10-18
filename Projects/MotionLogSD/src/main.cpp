/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Log Motion data to SD card
 * @date   2021-10-17
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>
#include <math.h>

#include "driver/gpio.h"
#include "esp_task_wdt.h"
#include "esp_pm.h"

#include <string>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#include "BufferQ.hpp"
#include "I2CUtil.h"
#include "MPU6050.h"

extern "C" auto app_main() -> void;

#define SDA_PIN 23
#define SCL_PIN 22

#define MISO_PIN 19
#define MOSI_PIN 18
#define SCLK_PIN  5
#define CS_PIN   27
#define LED_PIN  13
#define BTN_PIN  12

#define SAMPLE_PRIORITY  10
#define LOG_PRIORITY     10
#define SAMPLE_PERIOD   166  // ms
#define COMPUTE_PERIOD  100  // ms
#define BUFFER_SIZE      64


#define MOUNT_POINT "/DATALOGGER"
auto DATAFILE = MOUNT_POINT"/data.csv";

struct DataFormat {
    uint32_t time;
    float ax, ay, az;
    float gx, gy, gz;
    float temp;
};

// Global buffer
BufferQ<DataFormat, BUFFER_SIZE> buffer;
sdmmc_card_t *card = nullptr;
FILE* file         = nullptr;
float data[BUFFER_SIZE];
bool isLogging     = false;

uint32_t time_ms() {
    return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

void sample_task(void* args) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    MPU6050 mpu;
    MPU6050_Config(MPU6050_PWR_MGMT_1, 0x00);
    MPU6050_Config(MPU6050_SMPLRT_DIV, 250);
    MPU6050_AccConfig(0x00);

    bool prevState = false;
    bool currState = false;

    prevState = currState;
    currState = !gpio_get_level(gpio_num_t(BTN_PIN));
    for(;;) {
        MPU6050_Update(&mpu);  // Get accelerations
        prevState = currState;
        currState = !gpio_get_level(gpio_num_t(BTN_PIN));

        float mag = sqrtf(mpu.accx * mpu.accx +
                          mpu.accy * mpu.accy +
                          mpu.accz * mpu.accz);  // Compute magnitude
        if (currState && !prevState) {
            isLogging = !isLogging;
            gpio_set_level(gpio_num_t(LED_PIN), isLogging);
            if (isLogging) {
                file = fopen(DATAFILE, "a");
                if (file != nullptr) fprintf(file, "time,ax,ay,az,gx,gy,gz,temp\n");
            } else {
                if (file != nullptr) {
                    fclose(file);
                    file = nullptr;
                }
            }
        }
        // Add to buffer
        buffer.Enqueue({
                time_ms(),
                mpu.accx,  mpu.accy,  mpu.accz,
                mpu.gyrox, mpu.gyroy, mpu.gyroz,
                mpu.temp
            });
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SAMPLE_PERIOD));
    }
}

void log_task(void* args) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // Refer to https://github.com/espressif/esp-idf/blob/master/examples/storage/sd_card/sdspi/main/sd_card_example_main.c
    esp_vfs_fat_mount_config_t mountConfig = {
        .format_if_mount_failed = false,
        .max_files              = 5,
        .allocation_unit_size   = 16 * 1024
    };
    auto mountPoint = MOUNT_POINT;

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t busConfig = {
        .mosi_io_num = MOSI_PIN,
        .miso_io_num = MISO_PIN,
        .sclk_io_num = SCLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
        .flags           = 0,
        .intr_flags      = 0
    };
    auto err = spi_bus_initialize(spi_host_device_t(host.slot), &busConfig, 1);
    ESP_ERROR_CHECK(err);

    sdspi_device_config_t slotConfig = SDSPI_DEVICE_CONFIG_DEFAULT();
    slotConfig.gpio_cs = gpio_num_t(CS_PIN);
    slotConfig.host_id = spi_host_device_t(host.slot);
    err = esp_vfs_fat_sdspi_mount(mountPoint, &host, &slotConfig, &mountConfig, &card);
    ESP_ERROR_CHECK(err);
    sdmmc_card_print_info(stdout, card);  // Print SD card info

    for(;;) {
        while(!buffer.IsEmpty()) {
            auto const data = buffer.Dequeue();
            if (file != nullptr && isLogging) {
                fprintf(file, "%u,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",
                        data.time, data.ax, data.ay, data.az,
                        data.gx,   data.gy, data.gz, data.temp);
            }
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMPUTE_PERIOD));
    }

    esp_vfs_fat_sdcard_unmount(mountPoint, card);
    spi_bus_free(spi_host_device_t(host.slot));
}

auto app_main() -> void {
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

    // Initialise LED Pin
    gpio_config_t config;
    config.pin_bit_mask = uint64_t(1) << LED_PIN;
    config.mode         = gpio_mode_t(GPIO_MODE_OUTPUT);
    config.pull_up_en   = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&config));
    config.pin_bit_mask = uint64_t(1) << BTN_PIN;
    config.mode         = gpio_mode_t(GPIO_MODE_INPUT);
    config.pull_down_en = GPIO_PULLDOWN_ENABLE;
    config.pull_up_en   = GPIO_PULLUP_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&config));

    xTaskCreate(sample_task, "SampleTask", 2048, NULL, SAMPLE_PRIORITY, nullptr);
    xTaskCreate(log_task,    "LogTask",    5120, NULL, LOG_PRIORITY,    nullptr);
}

