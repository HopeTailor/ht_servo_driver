# HT Servo Driver for ESP32

A professional, hardware-driven C library for controlling Servo motors using the ESP32 MCPWM peripheral. Built for ESP-IDF / PlatformIO.

## ⚙️ How It Works (MCPWM Architecture)
Unlike simple software delays or basic LED PWM, this driver utilizes the ESP32's **Motor Control Pulse Width Modulator (MCPWM)** for precise, jitter-free signal generation. 

The `ht_servo_init` function configures four dedicated hardware blocks to generate the perfect square wave:

1. **Timer:** Configured with a 1MHz resolution to generate a strict **50Hz (20ms period)** base frequency, which is the standard heartbeat for RC servos.
2. **Operator:** Acts as the central bridge connecting the Timer to the control logic.
3. **Comparator:** Stores the exact requested pulse width (in microseconds). It constantly monitors the Timer and triggers an event the moment the time is reached.
4. **Generator:** Routes the logic to the physical GPIO pin. We configure it with two precise actions:
   - Drive the pin **HIGH** when the Timer resets (starts a new cycle).
   - Drive the pin **LOW** when the Timer matches the Comparator value.

## 🚀 Features
- **Hardware-Driven PWM:** Zero CPU overhead after initialization.
- **Configurable Parameters:** Adjust `min_pulse_width`, `max_pulse_width`, and `max_angle` to support any standard (e.g., 180°, 270°) or continuous rotation servo.
- **Safety Clamp:** Prevents mechanical gear damage by strictly clamping the requested angle to the physical maximum.
- **Object-Oriented Design:** Control multiple servos seamlessly by instantiating multiple `ht_servo_t` structures on different GPIOs and MCPWM groups.

## 🛠️ Installation (ESP-IDF / PlatformIO)
Clone this repository or copy the `ht_servo` folder into your project's `components/` directory. The ESP-IDF CMake build system will automatically detect and compile it.

## 💡 Quick Start Example

```c
#include "ht_servo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void) {
    // 1. Define the physical and hardware characteristics
    ht_servo_t my_servo = {
        .group_id = 0,
        .gpio_num = 18,
        .max_angle = 180.0f,
        .min_pulse_width_us = 500,
        .max_pulse_width_us = 2500
    };

    // 2. Initialize the MCPWM hardware engine
    ht_servo_init(&my_servo);

    // 3. Move the servo
    while(1) {
        ht_servo_set_angle(&my_servo, 0.0f);
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        ht_servo_set_angle(&my_servo, 180.0f);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}