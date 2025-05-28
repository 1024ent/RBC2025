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
    /*
        for (;;) {
        int currentBtn = buttonValue;

        if (currentBtn == 6 && !isRunning && !resetRequired) {

        }

        // Only button 9 (L1) can reset the mechanism
        if (currentBtn == 9 && !isRunning) {
            resetRequired = false;
        }

        vTaskDelay(10);  // CPU breathing room
    }
    */
}
#endif
 