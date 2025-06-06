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
MD motorZ(PWM_DIR,PWM_Z,DIR_Z);
MD motorY(PWM_DIR,PWM_Y,DIR_Y);

void dribbling_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function
    bool isRunning = false;
    bool resetRequired = false;

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

    enum class MotorState {
        IDLE,
        MOVING_UP,
        REVERSING,
        STOPPED,
        WAITING_FOR_RELEASE
    };

    MotorState state = MotorState::IDLE;
    const int upSpeed = 150;
    const int reverseSpeed = -64;
    const unsigned long reverseDuration = 300; // ms
    bool buttonWasPressed = false;

    for (;;) {
        int currentBtn = buttonValue;
        bool buttonIsPressed = (currentBtn == 3); // Button 3 is UP

        switch(state) {
            case MotorState::IDLE:
                if(buttonIsPressed && !buttonWasPressed) {
                    // Start movement on button press (edge detection)
                    motorZ.setSpeed(upSpeed);
                    state = MotorState::MOVING_UP;
                }
                break;

            case MotorState::MOVING_UP:
                if(digitalRead(LIM_Z1) == LOW) {
                    // Limit switch triggered
                    motorZ.setSpeed(reverseSpeed);
                    state = MotorState::REVERSING;
                } else if (!buttonIsPressed) {
                    // Emergency stop if button released during movement
                    motorZ.setSpeed(0);
                    state = MotorState::IDLE;
                }
                break;

            case MotorState::REVERSING:
                vTaskDelay(pdMS_TO_TICKS(reverseDuration));
                motorZ.setSpeed(0);
                state = MotorState::STOPPED;
                break;

            case MotorState::STOPPED:
                state = MotorState::WAITING_FOR_RELEASE;
                break;

            case MotorState::WAITING_FOR_RELEASE:
                if(!buttonIsPressed) {
                    state = MotorState::IDLE; // Reset only when button is released
                }
                break;
        }

        buttonWasPressed = buttonIsPressed; // Track previous button state
        vTaskDelay(pdMS_TO_TICKS(10));  // Use proper FreeRTOS macro
    }   
}

void lowering_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function

    enum class MotorState {
        IDLE,
        MOVING_DOWN,
        REVERSING,
        STOPPED,
        WAITING_FOR_RELEASE
    };

    MotorState state = MotorState::IDLE;
    const int downSpeed = -150;
    const int reverseSpeed = 64;
    const unsigned long reverseDuration = 300; // ms
    bool buttonWasPressed = false;

    for (;;) {
        int currentBtn = buttonValue;
        bool buttonIsPressed = (currentBtn == 2); // Button 2 is DOWN

        switch(state) {
            case MotorState::IDLE:
                if(buttonIsPressed && !buttonWasPressed) {
                    // Start movement on button press (edge detection)
                    motorZ.setSpeed(downSpeed);
                    state = MotorState::MOVING_DOWN;
                }
                break;

            case MotorState::MOVING_DOWN:
                if(digitalRead(LIM_Z2) == LOW) {
                    // Limit switch triggered
                    motorZ.setSpeed(reverseSpeed);
                    state = MotorState::REVERSING;
                } else if (!buttonIsPressed) {
                    // Emergency stop if button released during movement
                    motorZ.setSpeed(0);
                    state = MotorState::IDLE;
                }
                break;

            case MotorState::REVERSING:
                vTaskDelay(pdMS_TO_TICKS(reverseDuration));
                motorZ.setSpeed(0);
                state = MotorState::STOPPED;
                break;

            case MotorState::STOPPED:
                state = MotorState::WAITING_FOR_RELEASE;
                break;

            case MotorState::WAITING_FOR_RELEASE:
                if(!buttonIsPressed) {
                    state = MotorState::IDLE; // Reset only when button is released
                }
                break;
        }

        buttonWasPressed = buttonIsPressed; // Track previous button state
        vTaskDelay(pdMS_TO_TICKS(10));  // Use proper FreeRTOS macro
    }   
}

void yaw_forward_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function

    enum class MotorState {
        IDLE,
        MOVING_FRONT,
        REVERSING,
        STOPPED,
        WAITING_FOR_RELEASE
    };

    MotorState state = MotorState::IDLE;
    const int frontSpeed = -150;
    const int reverseSpeed = 64;
    const unsigned long reverseDuration = 300; // ms
    bool buttonWasPressed = false;

    for (;;) {
        int currentBtn = buttonValue;
        bool buttonIsPressed = (currentBtn == 1); // Button 1 is RIGHT

        switch(state) {
            case MotorState::IDLE:
                if(buttonIsPressed && !buttonWasPressed) {
                    // Start movement on button press (edge detection)
                    motorY.setSpeed(frontSpeed);
                    state = MotorState::MOVING_FRONT;
                }
                break;

            case MotorState::MOVING_FRONT:
                if(digitalRead(LIM_Y1) == LOW) {
                    // Limit switch triggered
                    motorY.setSpeed(reverseSpeed);
                    state = MotorState::REVERSING;
                } else if (!buttonIsPressed) {
                    // Emergency stop if button released during movement
                    motorY.setSpeed(0);
                    state = MotorState::IDLE;
                }
                break;

            case MotorState::REVERSING:
                vTaskDelay(pdMS_TO_TICKS(reverseDuration));
                motorY.setSpeed(0);
                state = MotorState::STOPPED;
                break;

            case MotorState::STOPPED:
                state = MotorState::WAITING_FOR_RELEASE;
                break;

            case MotorState::WAITING_FOR_RELEASE:
                if(!buttonIsPressed) {
                    state = MotorState::IDLE; // Reset only when button is released
                }
                break;
        }

        buttonWasPressed = buttonIsPressed; // Track previous button state
        vTaskDelay(pdMS_TO_TICKS(10));  // Use proper FreeRTOS macro
    } 
}

void yaw_backward_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function

    enum class MotorState {
        IDLE,
        MOVING_BACK,
        REVERSING,
        STOPPED,
        WAITING_FOR_RELEASE
    };

    MotorState state = MotorState::IDLE;
    const int backSpeed = 150;
    const int reverseSpeed = -64;
    const unsigned long reverseDuration = 300; // ms
    bool buttonWasPressed = false;

    for (;;) {
        int currentBtn = buttonValue;
        bool buttonIsPressed = (currentBtn == 4); // Button 4 is LEFT

        switch(state) {
            case MotorState::IDLE:
                if(buttonIsPressed && !buttonWasPressed) {
                    // Start movement on button press (edge detection)
                    motorY.setSpeed(backSpeed);
                    state = MotorState::MOVING_BACK;
                }
                break;

            case MotorState::MOVING_BACK:
                if(digitalRead(LIM_Y2) == LOW) {
                    // Limit switch triggered
                    motorY.setSpeed(reverseSpeed);
                    state = MotorState::REVERSING;
                } else if (!buttonIsPressed) {
                    // Emergency stop if button released during movement
                    motorY.setSpeed(0);
                    state = MotorState::IDLE;
                }
                break;

            case MotorState::REVERSING:
                vTaskDelay(pdMS_TO_TICKS(reverseDuration));
                motorY.setSpeed(0);
                state = MotorState::STOPPED;
                break;

            case MotorState::STOPPED:
                state = MotorState::WAITING_FOR_RELEASE;
                break;

            case MotorState::WAITING_FOR_RELEASE:
                if(!buttonIsPressed) {
                    state = MotorState::IDLE; // Reset only when button is released
                }
                break;
        }

        buttonWasPressed = buttonIsPressed; // Track previous button state
        vTaskDelay(pdMS_TO_TICKS(10));  // Use proper FreeRTOS macro
    }
}

#endif
