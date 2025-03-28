/**
 * @file blink_manager.cpp
 * @brief Managing thread indicator
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

 #include <Arduino.h>
 #include "driver/gpio.h"
 #include "sdkconfig.h"
 #include "output_config.h"
 
/**
 * @brief Blinking LED1 as a thread indicator and PCB is working
 * @return PCB LED1 blinking
 */
void master_thread_indicator(void *pvParameters)
{
    for (;;)
    {
        gpio_set_level(BLINK_GPIO1, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO1, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void slave_thread_indicator(void *pvParameters)
{
    for (;;)
    {
        gpio_set_level(BLINK_GPIO1, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO1, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}