#include "ht_servo.h"

esp_err_t ht_servo_init(ht_servo_t *servo) {
    if(!servo) {
        return ESP_ERR_INVALID_ARG;
    }

    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEAULT,
        .resolution_hz = 1000000,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
        .period_ticks = 20000,
    };
    esp_err_t err = mcpwm_new_timer(&timer_config, &servo->timer);
    if(err != ESP_OK) {
        return err;
    }

    mcpwm_operator_config_t oper_config = {
        .group_id = 0,
    };
    err = mcpwm_new_operator(&oper_config, &servo->oper);
    if(err != ESP_OK) {
        return err;
    }

    err = mcpwm_operator_connect_timer(servo->oper, servo->timer);
    if(err != ESP_OK) {
        return err;
    }

    err = mcpwm_comparator_ser_compare_value(servo->cmpr, servo->min_pulse_width_us);
    if(err != ESP_OK) {
        return err;
    }

    mcpwm_generator_config_t gen_config = {
        .gen_gpio_num = servo->gpio_num,
    };
    err = mcpwm_new_generator(servo->oper, &gen_config, &servo->gen);
    if(err != ESP_OK) {
        return err;
    }

    err = mcpwm_generator_set_action_on_timer_event(servo->gen, MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH));
    if(err != ESP_OK) {
        return err;
    }

    err = mcpwm_generator_set_action_on_compare_event(servo->gen, MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, servo->cmpr, MCPWM_GEN_ACTION_LOW));
    if(err != ESP_OK) {
        return err;
    }

    err = mcpwm_timer_enable(servo->timer);
    if(err != ESP_OK) {
        return err;
    }

    err = mcpwm_timer_start_stop(servo->timer, MCPWM_TIMER_START_NO_STOP);
    if(err != ESP_OK) {
        return err;
    }
    
    return ESP_OK;
}