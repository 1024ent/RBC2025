/**
 * @file robot_movement_mecanum.cpp
 * @brief Controlling robot movement through PS4 Controllers
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 * @author Clement [ELPROG]
 */

#include "robot_movement.h"
#include "output_config.h"

#ifdef MASTER

#define DEADZONE 15
#define SPEED_MAX 255
#define SPEED_MIN 0

void robot_movement_omni(void *parameter)
{
    motor m1, m2, m3, m4;

    // Initialize each motor with its direction and PWM pins
    m1.init_data(MOTOR1_DIR, MOTOR1_PWM, 0);
    m2.init_data(MOTOR2_DIR, MOTOR2_PWM, 1);
    m3.init_data(MOTOR3_DIR, MOTOR3_PWM, 2);
    m4.init_data(MOTOR4_DIR, MOTOR4_PWM, 3);

    for (;;)
    {
        if (PS4.isConnected())
        {
            // Get joystick values
            float x = PS4.LStickX();       // Left/Right
            float y = PS4.LStickY();       // Forward/Backward
            float rotation = PS4.RStickX(); // Rotation

            // Apply deadzone
            if (abs(x) < DEADZONE) x = 0;
            if (abs(y) < DEADZONE) y = 0;
            if (abs(rotation) < DEADZONE) rotation = 0;

            // Debugging joystick input
            Serial.print("X: "); Serial.print(x);
            Serial.print(" Y: "); Serial.print(y);
            Serial.print(" R: "); Serial.println(rotation);

            // Calculate omni wheel velocities
            float v1 = -x + y - rotation; // Front Right
            float v2 =  x + y - rotation; // Rear Right
            float v3 = -x + y + rotation; // Rear Left
            float v4 =  x + y + rotation; // Front Left

            // Normalize velocity (if needed)
            float maxVal = max(max(abs(v1), abs(v2)), max(abs(v3), abs(v4)));
            if (maxVal > 128.0) {
                v1 = v1 * 128.0 / maxVal;
                v2 = v2 * 128.0 / maxVal;
                v3 = v3 * 128.0 / maxVal;
                v4 = v4 * 128.0 / maxVal;
            }

            // Set direction and speed based on sign and magnitude
            m1.set_direction(v4 < 0 ? HIGH : LOW);
            m1.set_spin(constrain(abs(v4) * 2, SPEED_MIN, SPEED_MAX)); // *2 to scale to 255

            m2.set_direction(v1 < 0 ? HIGH : LOW);
            m2.set_spin(constrain(abs(v1) * 2, SPEED_MIN, SPEED_MAX));

            m3.set_direction(v2 < 0 ? HIGH : LOW);
            m3.set_spin(constrain(abs(v2) * 2, SPEED_MIN, SPEED_MAX));

            m4.set_direction(v3 < 0 ? HIGH : LOW);
            m4.set_spin(constrain(abs(v3) * 2, SPEED_MIN, SPEED_MAX));
        }

        // Avoid hogging CPU in RTOS
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

#endif
