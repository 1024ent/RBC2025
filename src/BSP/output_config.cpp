/**
 * @file output_config.cpp
 * @brief Output pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "output_config.h"
#include "motor_driver.h"

#ifdef MASTER
/**
 * @brief Initialising output instances for master
 */
void master_init_output_instances(){
    /** THREAD INDICATOR **/
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
}
#endif

#ifdef SLAVE
/**
 * @brief Initialising output instances for slave
 */
void slave_init_output_instances(){
    /** THREAD INDICATOR **/
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
    
    pinMode(RELAY1_PIN, OUTPUT);        // Relay 1 control pin
    pinMode(RELAY2_PIN, OUTPUT);        // Relay 2 control pin
}
#endif
  