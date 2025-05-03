/**
 * @file robot_movement_mecanum.cpp
 * @brief Controlling robot movement through PS4 Controllers
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#include "robot_movement.h"
#include "output_config.h"

#ifdef MASTER 

#define DEADZONE   15
#define MAX_SPEED  255
#define MID_SPEED  200
#define MIN_SPEED  0

// Helper for deadzone
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

            // Forward/Backward
            if (ly > 0 && lx == 0) {
                m1.move(LOW, ly);
                m2.move(LOW, ly);
                m3.move(LOW, ly);
                m4.move(LOW, ly);
                Serial.println("Forward");
            }
            else if (ly < 0 && lx == 0) {
                m1.move(HIGH, -ly);
                m2.move(HIGH, -ly);
                m3.move(HIGH, -ly);
                m4.move(HIGH, -ly);
                Serial.println("Backward");
            }
            // Left/Right
            else if (lx < 0 && ly == 0) {
                m1.move(LOW, -lx);
                m2.move(HIGH, -lx);
                m3.move(LOW, -lx);
                m4.move(HIGH, -lx);
                Serial.println("Left");
            }
            else if (lx > 0 && ly == 0) {
                m1.move(HIGH, lx);
                m2.move(LOW, lx);
                m3.move(HIGH, lx);
                m4.move(LOW, lx);
                Serial.println("Right");
            }
            // Diagonal directions
            else if (lx < -30 && ly > 30) {
                m1.set_spin(MIN_SPEED);
                m2.move(LOW, MID_SPEED);
                m3.set_spin(MIN_SPEED);
                m4.move(LOW, MID_SPEED);
                Serial.println("Top Left");
            }
            else if (lx > 30 && ly > 30) {
                m1.move(LOW, MID_SPEED);
                m2.set_spin(MIN_SPEED);
                m3.move(LOW, MID_SPEED);
                m4.set_spin(MIN_SPEED);
                Serial.println("Top Right");
            }
            else if (lx > 30 && ly < -30) {
                m1.move(HIGH, MID_SPEED);
                m2.set_spin(MIN_SPEED);
                m3.move(HIGH, MID_SPEED);
                m4.set_spin(MIN_SPEED);
                Serial.println("Bottom Right");
            }
            else if (lx < -30 && ly < -30) {
                m1.set_spin(MIN_SPEED);
                m2.move(HIGH, MID_SPEED);
                m3.set_spin(MIN_SPEED);
                m4.move(HIGH, MID_SPEED);
                Serial.println("Bottom Left");
            }
            // Rotation CW / CCW
            else if (rx > 30) {
                int speed = map(rx, 30, 128, MID_SPEED, MAX_SPEED);
                m1.move(HIGH, speed);
                m2.move(HIGH, speed);
                m3.move(LOW, speed);
                m4.move(LOW, speed);
                Serial.println("Rotate CW");
            }
            else if (rx < -30) {
                int speed = map(rx, -128, -30, MAX_SPEED, MID_SPEED);
                m1.move(LOW, speed);
                m2.move(LOW, speed);
                m3.move(HIGH, speed);
                m4.move(HIGH, speed);
                Serial.println("Rotate CCW");
            }
            else {
                // STOP all
                m1.set_spin(MIN_SPEED);
                m2.set_spin(MIN_SPEED);
                m3.set_spin(MIN_SPEED);
                m4.set_spin(MIN_SPEED);
                //Serial.println("Stop");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

#endif
 