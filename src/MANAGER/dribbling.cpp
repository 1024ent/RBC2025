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
extern int buttonValue;  // Import button value

void dribbling_mechanism(void *parameter) {
    Stepper stepper(Stepper::DRIVER, STEPPER1_PUL, STEPPER1_DIR);

    unsigned long previousMillis = 0;
    const long interval = 10000;  // 10 seconds
    int direction = 1;  // 1 for clockwise, -1 for anti-clockwise

    // Set stepper motor parameters
    stepper.setMaxSpeed(1000);    // Max speed (steps per second)
    stepper.setAcceleration(500); // Acceleration (steps per second squared)

    // Move the motor clockwise for 10 seconds
    unsigned long startTime = millis();

    for(;;) {
        unsigned long currentMillis = millis();

        // Change direction every 10 seconds
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          direction *= -1;  // Toggle direction
        }
      
        // Set the motor speed based on the direction
        if (direction == 1) {
          stepper.setSpeed(1000);  // Set clockwise speed
        } else {
          stepper.setSpeed(-1000);  // Set anti-clockwise speed
        }
      
        // Run the motor continuously in the set direction
        stepper.runSpeed();        
    }
}

#endif