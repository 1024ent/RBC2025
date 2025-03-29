/**
 * @file robot_movement_mecanum.cpp
 * @brief Controlling robot movement through PS4 Controllers
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 */

#include "robot_movement.h"
#include "output_config.h"
#include "uart_manager.h"

#ifdef SLAVE
extern int LStickX;  // Import from uart_manager.cpp
extern int LStickY;  // Import from uart_manager.cpp
extern int buttonValue;  // Import button value

#define DEADZONE 15
#define SPEED_MAX 255
#define SPEED_MID 200
#define SPEED_MIN 0

void robot_movement_omni(void *parameter)
{
    motor m1, m2, m3, m4;

    m1.init_data(MOTOR1_DIR, MOTOR1_PWM, 0);
    m2.init_data(MOTOR2_DIR, MOTOR2_PWM, 1);
    m3.init_data(MOTOR3_DIR, MOTOR3_PWM, 2);
    m4.init_data(MOTOR4_DIR, MOTOR4_PWM, 3);

    for (;;)
    {
        // Get latest values from UART task
        int currentLX = LStickX;
        int currentLY = LStickY;
        int currentBtn = buttonValue;  // Available for future use
        
        // Debug output
        Serial.printf("[MOTION] LX:%d LY:%d BTN:%d\n", currentLX, currentLY, currentBtn);

        // Apply deadzone
        if (abs(currentLX) < DEADZONE) currentLX = 0;
        if (abs(currentLY) < DEADZONE) currentLY = 0;

        // Now, use LStickX and LStickY for movement
        if ((LStickY > 5) && (LStickX < 29) && (LStickX > -29))
        {
            m1.set_direction(LOW);
            m1.set_spin(SPEED_MAX);
            m2.set_direction(HIGH);
            m2.set_spin(SPEED_MAX);
            m3.set_direction(LOW);
            m3.set_spin(SPEED_MAX);
            m4.set_direction(HIGH);
            m4.set_spin(SPEED_MAX);
            Serial.println("Robot Forward");
        }
        else if ((LStickY < -5) && (LStickX < 29) && (LStickX > -29))
        {
            m1.set_direction(HIGH);
            m1.set_spin(SPEED_MAX);
            m2.set_direction(LOW);
            m2.set_spin(SPEED_MAX);
            m3.set_direction(HIGH);
            m3.set_spin(SPEED_MAX);
            m4.set_direction(LOW);
            m4.set_spin(SPEED_MAX);
            Serial.println("Robot Backward");
        }
        else
        {
            m1.set_spin(SPEED_MIN);
            m2.set_spin(SPEED_MIN);
            m3.set_spin(SPEED_MIN);
            m4.set_spin(SPEED_MIN);
            Serial.println("Robot STOP");
        }

        vTaskDelay(pdMS_TO_TICKS(50));  // Small delay to avoid flooding UART
    }
}
#endif
