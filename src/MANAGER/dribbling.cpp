#include "dribbling.h"
/**
 * @file dribbling.cpp
 * @brief Managing Dribbling Mechanism
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#include "dribbling.h"
#include "output_config.h"
#include "uart_manager.h"
#include "stepper.h"

#ifdef SLAVE
extern int buttonValue;  // Shared variable updated by UART receive function

void dribbling_mechanism(void *parameter) {
    Stepper stepper(Stepper::DRIVER, STEPPER1_PUL, STEPPER1_DIR);

    const long runDuration = 5000;  // 5 seconds
    bool hasRun = false;            // To prevent repeating unless button is pressed again

    // Stepper motor settings
    stepper.setMaxSpeed(1000);      // max speed in steps/sec
    stepper.setAcceleration(500);   // acceleration in steps/sec^2

    for (;;) {
        int currentBtn = buttonValue;

        if (currentBtn == 6 && !hasRun) {  // Triangle button pressed and not run yet
            hasRun = true;

            // Run CW for 5 seconds
            unsigned long startTime = millis();
            while (millis() - startTime < runDuration) {
                stepper.setSpeed(1000);
                stepper.runSpeed();
                vTaskDelay(1);
            }

            // Run CCW for 5 seconds
            startTime = millis();
            while (millis() - startTime < runDuration) {
                stepper.setSpeed(-1000);
                stepper.runSpeed();
                vTaskDelay(1);
            }

            // Stop the motor
            stepper.setSpeed(0);
        }

        // Reset hasRun flag when button is released
        if (currentBtn != 6) {
            hasRun = false;
        }

        vTaskDelay(10);  // Small delay to let CPU breathe
    }
}
#endif
 
 