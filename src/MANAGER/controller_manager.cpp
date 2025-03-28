/**
 * @file controller_manager.cpp
 * @brief Managing PS4 Controller Information
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 */

#include <Arduino.h>
#include "PS4Controller.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "controller_manager.h"

/**
 * @brief Get battery percentage of controller
 * @details Indicating the battery percentage value every 5 seconds
 * @return Battery percentage
 */
void controller_manager(void *pvParameters)
{
    for (;;)
    {
        if (PS4.isConnected())
        {
            int batteryValue = PS4.Battery();
            int fullBatteryValue = 10;

            int batteryPercentage = (batteryValue * 100) / fullBatteryValue;

            Serial.printf("[CONTROLLER_MGR] : Battery Level: %d%%", batteryPercentage);
            Serial.println();
            delay(5000);
        }
    }
}
