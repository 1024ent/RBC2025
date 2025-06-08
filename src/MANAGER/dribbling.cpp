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
#include "esp_task_wdt.h"

#ifdef SLAVE
MD motorZ(PWM_DIR,PWM_Z,DIR_Z);
MD motorY(PWM_DIR,PWM_Y,DIR_Y);

void semi_auto(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function
    // Add watchdog timer to prevent crashes
    esp_task_wdt_init(10, false); // 10-second timeout

    enum class MotorAction {
        IDLE,
        FRONT,
        BACK,
        REVERSING,
        DRIBBLE,
        RELOAD
        // Removed WAITING_FOR_RELEASE as it wasn't needed in the sequence
    };

    MotorAction currentAction = MotorAction::IDLE;
    MotorAction previousAction = MotorAction::IDLE;
    
    const int normalSpeed = 150;       // Speed moving toward front/back
    const int reverseSpeed = 64;      // Speed during reversing (could be different)
    const TickType_t reverseDuration = pdMS_TO_TICKS(800);
    TickType_t reverseStartTime = 0;
    bool buttonWasPressed = false;


    for (;;) {
        int currentBtn = buttonValue;
        bool buttonIsPressed = (currentBtn == 9); // Button 9 is L1
        
        switch(currentAction) {
            case MotorAction::IDLE:
                if (buttonIsPressed && !buttonWasPressed) {
                    // Start sequence on button press
                    motorY.setSpeed(-normalSpeed);  // Move toward front
                    currentAction = MotorAction::FRONT;
                }
                break;

            case MotorAction::FRONT:
                if (digitalRead(LIM_Y1) == LOW) {
                    motorY.setSpeed(reverseSpeed);  // Start reversing
                    previousAction = currentAction;
                    reverseStartTime = xTaskGetTickCount();
                    currentAction = MotorAction::REVERSING;
                    
                }
                break;
            
            case MotorAction::DRIBBLE:
                motorY.setSpeed(0);             // Stop motor Y for 2 seconds
                vTaskDelay(pdMS_TO_TICKS(1000));
                // Turn on both relays
                digitalWrite(RELAY1_PIN, HIGH);
                digitalWrite(RELAY2_PIN, HIGH);
                Serial.println("Dribbling: Both relays ON");
                
                vTaskDelay(pdMS_TO_TICKS(400));
                digitalWrite(RELAY2_PIN, LOW);
                Serial.println("Dribbling: Relay 2 OFF");
                
                vTaskDelay(pdMS_TO_TICKS(250));
                digitalWrite(RELAY1_PIN, LOW);
                
                // Move back after dribbling
                motorY.setSpeed(0);             // Stop motor Y for 2 seconds
                vTaskDelay(pdMS_TO_TICKS(2000));
                motorY.setSpeed(normalSpeed);   // Move toward back
                currentAction = MotorAction::BACK;
                break;

            case MotorAction::BACK:
                if (digitalRead(LIM_Y2) == LOW) {
                    motorY.setSpeed(-reverseSpeed);  // Start reversing
                    previousAction = currentAction;
                    reverseStartTime = xTaskGetTickCount();
                    currentAction = MotorAction::REVERSING;
                }
                break;

            case MotorAction::RELOAD:
                // Turn on both relays for reload
                vTaskDelay(pdMS_TO_TICKS(700));
                digitalWrite(RELAY1_PIN, HIGH);
                //digitalWrite(RELAY2_PIN, HIGH);
                Serial.println("Reloading: Both relays ON");
                
                vTaskDelay(pdMS_TO_TICKS(1500));

                digitalWrite(RELAY1_PIN, LOW);
                //digitalWrite(RELAY2_PIN, LOW);
                
                currentAction = MotorAction::IDLE;  // Sequence complete
                break;

            case MotorAction::REVERSING:
                if ((xTaskGetTickCount() - reverseStartTime) >= reverseDuration) {
                    motorY.setSpeed(0);  // Stop motor
                    
                    // Determine next action
                    if (previousAction == MotorAction::FRONT) {
                        currentAction = MotorAction::DRIBBLE;
                    } 
                    else if (previousAction == MotorAction::BACK) {
                        currentAction = MotorAction::RELOAD;
                    }
                }
                break;
        }
        buttonWasPressed = buttonIsPressed;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

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
        if (currentBtn != 5 && !isRunning) {
            resetRequired = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void reload_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function
    bool isRunning = false;
    bool resetRequired = false;

    digitalWrite(RELAY1_PIN, LOW);  // Relay 1 OFF (active LOW)
    digitalWrite(RELAY2_PIN, LOW);  // Relay 2 OFF (active LOW)

    for (;;) {
        int currentBtn = buttonValue;

        // Button 11 (L2) starts the ball release mechanism
        if (currentBtn == 11 && !isRunning && !resetRequired) {
            isRunning = true;

            // Turn on both relays for reload
            vTaskDelay(pdMS_TO_TICKS(700));
            digitalWrite(RELAY1_PIN, HIGH);

            vTaskDelay(pdMS_TO_TICKS(700));
            digitalWrite(RELAY1_PIN, LOW);

            resetRequired = true;
            isRunning = false;
        }
        if (currentBtn != 11 && !isRunning) {
            resetRequired = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
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
                if(digitalRead(LIM_Z2) == LOW) {  // Changed to lim_down
                    // Limit switch triggered
                    motorZ.setSpeed(reverseSpeed);
                    state = MotorState::REVERSING;
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
                if(digitalRead(LIM_Y2) == LOW) {  // Changed to lim_back for back movement
                    // Limit switch triggered
                    motorY.setSpeed(reverseSpeed);
                    state = MotorState::REVERSING;
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
