#pragma once

#include <stdint.h>
#include "esp_err.h"
#include "driver/mcpwm_prelude.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configuration and state structure for a servo motor.
 * 
 * This structure holds both the user-defined configuration parameters
 * and the internal hardware handles required by the MCPWM driver.
 */
typedef struct {
    /* --- User Configuration Parameters --- */
    
    /** @brief MCPWM group ID (0 or 1). Determines which hardware block is used. */
    int group_id;                   
    
    /** @brief GPIO pin number connected to the servo's signal wire. */
    int gpio_num;                   
    
    /** @brief Maximum physical rotation angle of the servo in degrees (e.g., 180.0, 270.0). */
    float max_angle;                
    
    /** @brief Pulse width in microseconds corresponding to 0 degrees (typically 500 or 1000). */
    uint32_t min_pulse_width_us;    
    
    /** @brief Pulse width in microseconds corresponding to max_angle (typically 2000 or 2500). */
    uint32_t max_pulse_width_us;    

    /* --- Internal Hardware Handles (Do not modify manually) --- */
    mcpwm_timer_handle_t timer;     /*!< Handle for the MCPWM timer */
    mcpwm_oper_handle_t oper;       /*!< Handle for the MCPWM operator */
    mcpwm_cmpr_handle_t cmpr;       /*!< Handle for the MCPWM comparator */
    mcpwm_gen_handle_t gen;         /*!< Handle for the MCPWM generator */
} ht_servo_t;

/**
 * @brief Initialize the servo motor hardware using ESP32 MCPWM.
 * 
 * This function configures the hardware timer to generate a 50Hz (20ms) 
 * PWM signal. It securely links the timer, operator, comparator, and generator.
 * 
 * @param[in,out] servo Pointer to the servo configuration structure.
 *                      The configuration fields must be set before calling this function.
 * 
 * @return 
 *      - ESP_OK: Hardware initialized successfully.
 *      - ESP_ERR_INVALID_ARG: Null pointer provided.
 *      - Other ESP_ERR_* codes indicating hardware allocation failure.
 */
esp_err_t ht_servo_init(ht_servo_t *servo);

/**
 * @brief Set the target angle of the servo motor.
 * 
 * Converts the desired angle into the required pulse width using linear mapping.
 * The input angle is strictly clamped between 0 and max_angle to prevent 
 * mechanical damage to the servo gears.
 * 
 * @param[in] servo Pointer to the initialized servo structure.
 * @param[in] angle Target angle in degrees.
 * 
 * @return 
 *      - ESP_OK: New angle applied successfully.
 *      - ESP_ERR_INVALID_ARG: Null pointer provided.
 */
esp_err_t ht_servo_set_angle(ht_servo_t *servo, float angle);

#ifdef __cplusplus
}
#endif