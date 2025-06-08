/**
 * @file robot_movement.h
 * @brief Controlling robot movement through PS4 Controllers
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Mahendran King [ELPROG]
 * @author Pravin Thiruchelvam [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */
#include "shooting.h"
#include "robot_movement.h"
#include "output_config.h"
#include "uart_manager.h"

#ifdef SLAVE

#define MOTOR_STOP 0
#define MOTOR_SLOW_1 127.5 //125
#define MOTOR_SLOW_2 127.5 //127.5
#define MOTOR_FAST_1 255 //250
#define MOTOR_FAST_2 255

void shooting_mechanism(void *parameter) {
    extern int buttonValue;  // Shared variable updated by UART receive function
    bool isRunning = false;
    bool resetRequired = false;

    // SHOOTING MECHANISM RELAY
    pinMode(SHOOT_RELAY, OUTPUT);
    digitalWrite(SHOOT_RELAY, HIGH);

    // SHOOTING MECHANISM MOTORS
    // Set PWM frequency (19000Hz, commonly used for motor control)
    ledcSetup(4, 18000, 8);  // Channel 0 for Left Motor PWM
    ledcSetup(5, 18000, 8);  // Channel 1 for Right Motor PWM
        
    // Attach PWM pins to the channels
    ledcAttachPin(SHOOT_PWM_L, 4);   // Left motor PWM
    ledcAttachPin(SHOOT_PWM_R, 5);  // Right motor PWM

    // Set initial motor speed to stop
    ledcWrite(4, MOTOR_STOP);
    ledcWrite(5, MOTOR_STOP);

    for (;;) {
        int currentBtn = buttonValue;

        if (currentBtn == 7 && !isRunning && !resetRequired) {
            isRunning = true;

            // ---50% speed ---
            ledcWrite(4, MOTOR_SLOW_2);
            ledcWrite(5, MOTOR_SLOW_1);
            digitalWrite(SHOOT_DIR_L, LOW);  // Motor 1 forward
            digitalWrite(SHOOT_DIR_R, HIGH); // Motor 2 forward
            vTaskDelay(pdMS_TO_TICKS(1500));

            // --- 100% speed ---
            ledcWrite(4, MOTOR_FAST_2);
            ledcWrite(5, MOTOR_FAST_1);
            digitalWrite(SHOOT_DIR_L, LOW);  // Motor 1 forward
            digitalWrite(SHOOT_DIR_R, HIGH); // Motor 2 forward
            vTaskDelay(pdMS_TO_TICKS(500));
            digitalWrite(SHOOT_RELAY, LOW);
            vTaskDelay(pdMS_TO_TICKS(800));
            digitalWrite(SHOOT_RELAY, HIGH);

            // --- Relay active duration ---
            vTaskDelay(pdMS_TO_TICKS(3500));
            digitalWrite(SHOOT_RELAY, HIGH);

            // --- Slow down motors ---
            ledcWrite(4, MOTOR_SLOW_2);
            ledcWrite(5, MOTOR_SLOW_1);
            digitalWrite(SHOOT_DIR_L, LOW);  // Motor 1 forward
            digitalWrite(SHOOT_DIR_R, HIGH); // Motor 2 forward
            vTaskDelay(pdMS_TO_TICKS(1500));

            ledcWrite(4, MOTOR_STOP);
            ledcWrite(5, MOTOR_STOP);
            vTaskDelay(pdMS_TO_TICKS(3000));

            resetRequired = true;
            isRunning = false;
        }

        // Only button 9 (L1) can reset the mechanism
        if (currentBtn != 7 && !isRunning) {
            resetRequired = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));  // CPU breathing room
    }
}

#endif

