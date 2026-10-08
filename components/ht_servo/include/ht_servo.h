#pragma once

#include <stdint.h>
#include "esp_err.h"
#include "driver/mcpwm_prelude.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int gpio_num;
    float max_angle;
    uint32_t min_pulse_width_us;
    uint32_t max_pulse_width_us;
    mcpwm_timer_handle_t timer;
    mcpwm_oper_handle_t oper;
    mcpwm_cmpr_handle_t cmpr;
    mcpwm_gen_handle_t gen;
} ht_servo_t;

esp_err_t ht_servo_init(ht_servo_t *servo);

esp_err_t ht_servo_set_angle(ht_servo_t *servo, float angle);


#ifdef __cplusplus
}
#endif