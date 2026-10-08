#include <ht_servo.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "SERVO"

void app_main(void) {
    ESP_LOGI(TAG, "Starting servo test...");

    ht_servo_t servo = {
        .group_id = 0,
        .gpio_num = 18,
        .max_angle = 180.0f,
        .min_pulse_width_us = 500,
        .max_pulse_width_us = 2500
    };

    esp_err_t err = ht_servo_init(&servo);
    if(err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize servo!!!");
        return;
    }

    while(1) {
        ESP_LOGI(TAG, "Moving to 0 degrees");
        ht_servo_set_angle(&servo, 0.0f);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "Moving to 90 degrees");
        ht_servo_set_angle(&servo, 90.0f);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "Moving to 180 degrees");
        ht_servo_set_angle(&servo, 180.0f);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}