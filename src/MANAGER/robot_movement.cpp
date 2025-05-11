/**
 * @file robot_movement_mecanum.cpp
 * @brief Controlling robot movement through PS4 Controllers
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 * @author Lee Wen Hui [ELPROG]
 */

#include "robot_movement.h"
#include "output_config.h"
#include <math.h>

#ifdef MASTER

#define DEADZONE   15
#define MAX_SPEED  255
#define MID_SPEED  127
#define LOW_SPEED  63
#define MIN_SPEED  0

int applyDeadzone(int val) {
    return (abs(val) < DEADZONE) ? 0 : val;
}

void robot_movement_omni(void *parameter)
{
    motor m1, m2, m3, m4;

    m1.init_data(MOTOR1_DIR, MOTOR1_PWM, 0);
    m2.init_data(MOTOR2_DIR, MOTOR2_PWM, 1);
    m3.init_data(MOTOR3_DIR, MOTOR3_PWM, 2);
    m4.init_data(MOTOR4_DIR, MOTOR4_PWM, 3);

    for (;;)
    {
        if (PS4.isConnected())
        {
            int lx = applyDeadzone(PS4.LStickX());
            int ly = applyDeadzone(PS4.LStickY());
            int rx = applyDeadzone(PS4.RStickX());

            if (lx != 0 || ly != 0) {
                float angle = atan2(ly, lx) * 180.0 / PI; // convert to degrees

                // Normalize angle to -180 to +180
                if (angle > 180) angle -= 360;
                if (angle < -180) angle += 360;

                int speed = map(sqrt(lx*lx + ly*ly), 0, 127 * 1.41, MIN_SPEED, MAX_SPEED);
                // Clamp speed to avoid out of bound
                speed = constrain(speed, MIN_SPEED, MAX_SPEED);

                if (angle > -22.5 && angle <= 22.5) {
                    // Right
                    m1.move(HIGH, speed);
                    m2.move(LOW, speed);
                    m3.move(HIGH, speed);
                    m4.move(LOW, speed);
                    Serial.println("Right");
                }
                else if (angle > 22.5 && angle <= 67.5) {
                    // Top-Right
                    m1.move(LOW, speed);
                    m2.set_spin(MIN_SPEED);
                    m3.move(LOW, speed);
                    m4.set_spin(MIN_SPEED);
                    Serial.println("Top-Right");
                }
                else if (angle > 67.5 && angle <= 112.5) {
                    // Forward
                    m1.move(LOW, speed);
                    m2.move(LOW, speed);
                    m3.move(LOW, speed);
                    m4.move(LOW, speed);
                    Serial.println("Forward");
                }
                else if (angle > 112.5 && angle <= 157.5) {
                    // Top-Left
                    m1.set_spin(MIN_SPEED);
                    m2.move(LOW, speed);
                    m3.set_spin(MIN_SPEED);
                    m4.move(LOW, speed);
                    Serial.println("Top-Left");
                }
                else if (angle > 157.5 || angle <= -157.5) {
                    // Left
                    m1.move(LOW, speed);
                    m2.move(HIGH, speed);
                    m3.move(LOW, speed);
                    m4.move(HIGH, speed);
                    Serial.println("Left");
                }
                else if (angle > -157.5 && angle <= -112.5) {
                    // Bottom-Left
                    m1.set_spin(MIN_SPEED);
                    m2.move(HIGH, speed);
                    m3.set_spin(MIN_SPEED);
                    m4.move(HIGH, speed);
                    Serial.println("Bottom-Left");
                }
                else if (angle > -112.5 && angle <= -67.5) {
                    // Backward
                    m1.move(HIGH, speed);
                    m2.move(HIGH, speed);
                    m3.move(HIGH, speed);
                    m4.move(HIGH, speed);
                    Serial.println("Backward");
                }
                else if (angle > -67.5 && angle <= -22.5) {
                    // Bottom-Right
                    m1.move(HIGH, speed);
                    m2.set_spin(MIN_SPEED);
                    m3.move(HIGH, speed);
                    m4.set_spin(MIN_SPEED);
                    Serial.println("Bottom-Right");
                }
            }
            // Rotation only if no directional movement
            else if (rx > 30) {
                int speed = map(rx, 30, 127, MID_SPEED, MAX_SPEED);
                m1.move(HIGH, speed);
                m2.move(HIGH, speed);
                m3.move(LOW, speed);
                m4.move(LOW, speed);
                Serial.println("Rotate CW");
            }
            else if (rx < -30) {
                int speed = map(rx, -127, -30, MAX_SPEED, MID_SPEED);
                m1.move(LOW, speed);
                m2.move(LOW, speed);
                m3.move(HIGH, speed);
                m4.move(HIGH, speed);
                Serial.println("Rotate CCW");
            }
            else {
                m1.set_spin(MIN_SPEED);
                m2.set_spin(MIN_SPEED);
                m3.set_spin(MIN_SPEED);
                m4.set_spin(MIN_SPEED);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void robot_movement_omni_v2(void *parameter)
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
            m1.set_spin(constrain(abs(v4) * 2, MIN_SPEED, MAX_SPEED)); // *2 to scale to 255

            m2.set_direction(v1 < 0 ? HIGH : LOW);
            m2.set_spin(constrain(abs(v1) * 2, MIN_SPEED, MAX_SPEED));

            m3.set_direction(v2 < 0 ? HIGH : LOW);
            m3.set_spin(constrain(abs(v2) * 2, MIN_SPEED, MAX_SPEED));

            m4.set_direction(v3 < 0 ? HIGH : LOW);
            m4.set_spin(constrain(abs(v3) * 2, MIN_SPEED, MAX_SPEED));
        }

        // Avoid hogging CPU in RTOS
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

#endif
 