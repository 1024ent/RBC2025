/**
 * @file controller_manager.cpp
 * @brief Managing PS4 Controller Information
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
#include "PS4Controller.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "controller_manager.h"


#ifdef MASTER
int r = 255;
int g = 0;
int b = 0;

/**
 * @brief Calculating next rainbow PS4 LED sequence
 */
void nextRainbowColor() {
    int increment = 5;

    if (r > 0 && b == 0)
    {
        r -= increment;
        g += increment;
    }
    if (g > 0 && r == 0)
    {
        g -= increment;
        b += increment;
    }
    if (b > 0 && g == 0)
    {
        r += increment;
        b -= increment;
    }
}

/**
 * @brief Get battery percentage of controller
 * @details Indicating the battery percentage value every 5 seconds
 * @return Battery percentage
 */
void controller_manager(void *pvParameters) {
    const TickType_t delayTime = pdMS_TO_TICKS(5000); // Convert ms to ticks

    for (;;)
    {
        if (PS4.isConnected())
        {
            int batteryValue = PS4.Battery();
            const int fullBatteryValue = 10;

            int batteryPercentage = (batteryValue * 100) / fullBatteryValue;

            Serial.printf("[CONTROLLER_MGR] : Battery Level: %d%%\n", batteryPercentage);
        }
        vTaskDelay(delayTime); // Non-blocking delay
    }
}

/**
 * @brief Continuously sending commands to PS4 for LED sequence
 */
void controller_led_sequence(void *pvParameters) {
    const TickType_t delayTime = pdMS_TO_TICKS(100); // Convert ms to ticks

    for (;;)
    {
        PS4.setLed(r, g, b);
        nextRainbowColor();
        PS4.setFlashRate(0, 0);
        PS4.sendToController();

        vTaskDelay(delayTime); // Non-blocking delay
    }
}
#endif
