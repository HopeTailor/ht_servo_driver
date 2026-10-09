/**
 * @file main.c
 * @brief Example application to demonstrate the HT Servo motor driver.
 */

#include <ht_servo.h> 
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"
#include "esp_log.h" 

static const char *TAG = "SERVO";

void app_main(void) {
    ESP_LOGI(TAG, "Starting servo test..."); 

    /* 1. Define the physical and hardware characteristics of the servo */
    ht_servo_t servo = {
        .group_id = 0,               /*!< Use MCPWM group 0 */ 
        .gpio_num = 18,              /*!< Connect signal wire to GPIO 18 */ 
        .max_angle = 180.0f,         /*!< Servo physical limit is 180 degrees */ 
        .min_pulse_width_us = 500,   /*!< Pulse width for 0 degrees */ 
        .max_pulse_width_us = 2500   /*!< Pulse width for 180 degrees */ 
    };

    /* 2. Initialize the MCPWM hardware with the given configuration */
    esp_err_t err = ht_servo_init(&servo);
    if(err != ESP_OK) { 
        ESP_LOGE(TAG, "Failed to initialize servo!!!"); 
        return; 
    }

    /* 3. Main control loop: Sweep between 0, 90, and 180 degrees */
    while(1) { 
        ESP_LOGI(TAG, "Moving to 0 degrees"); 
        ht_servo_set_angle(&servo, 0.0f);
        vTaskDelay(pdMS_TO_TICKS(1000));  /*!< Wait for 1 second */

        ESP_LOGI(TAG, "Moving to 90 degrees");
        ht_servo_set_angle(&servo, 90.0f); 
        vTaskDelay(pdMS_TO_TICKS(1000)); 

        ESP_LOGI(TAG, "Moving to 180 degrees"); 
        ht_servo_set_angle(&servo, 180.0f); 
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}