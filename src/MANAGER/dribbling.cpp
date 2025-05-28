/**
 * @file dribbling.cpp
 * @brief Managing Dribbling Mechanism
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Al-Imran [ELPROG]
 * @author Khairuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#include "dribbling.h"
#include "output_config.h"
#include "uart_manager.h"
#include "input_config.h"
#include "motor_driver.h"

#ifdef SLAVE
void dribbling_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function
    bool isRunning = false;
    bool resetRequired = false;

    pinMode(RELAY1_PIN, OUTPUT);        // Relay 1 control pin
    pinMode(RELAY2_PIN, OUTPUT);        // Relay 2 control pin

    digitalWrite(RELAY1_PIN,LOW);     // Both OFF initially (active LOW)
    digitalWrite(RELAY2_PIN, LOW);
    
    for (;;) {
        int currentBtn = buttonValue;

        // Button 5 (SQUARE) starts the dribbling mechanism
        if (currentBtn == 5 && !isRunning && !resetRequired) {
            isRunning = true;

            // Turn both relays ON
            digitalWrite(RELAY1_PIN, HIGH); // Relay 1 ON
            //delay(50); 
            digitalWrite(RELAY2_PIN, HIGH);  
            // Relay 2 ON
    
            vTaskDelay(pdMS_TO_TICKS(400)); // Relay 2 ON duration
            digitalWrite(RELAY2_PIN, LOW);  // Relay 2 OFF
    
            vTaskDelay(pdMS_TO_TICKS(250)); // Remaining time for Relay 1
            digitalWrite(RELAY1_PIN, LOW);  // Relay 1 OFF

            resetRequired = true;
            isRunning = false;
        }

        // Only button 9 (L1) can reset the mechanism
        if (currentBtn != 5 && !isRunning) {
            resetRequired = false;
        }

        vTaskDelay(10);  // CPU breathing room
    }
}

void lifting_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function
    bool isRunning = false;
    bool resetRequired = false;

    pinMode(LIM_Z1, INPUT_PULLUP);
    pinMode(LIM_Z2, INPUT_PULLUP);
    pinMode(LIM_Y1, INPUT_PULLUP);
    pinMode(LIM_Y2, INPUT_PULLUP);

    MD motor_z(PWM_DIR,PICK_PWM_Z,PICK_DIR_Z);
    MD motor_y(PWM_DIR,PICK_PWM_Y,PICK_DIR_Y);

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
}

void lowering_mechanism(void *parameter) {

}

void yaw_forward_mechanism(void *parameter) {

}

void yaw_backward_mechanism(void *parameter) {

}

void ball_picking_mechanism(void *parameter){
    
}

#endif
