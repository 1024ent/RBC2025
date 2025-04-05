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
        if (PS4.isConnected())
        {
            int lx = PS4.LStickX();
            int ly = PS4.LStickY();
            int rx = PS4.RStickX();

            // Apply deadzone
            if (abs(lx) < DEADZONE) lx = 0;
            if (abs(ly) < DEADZONE) ly = 0;
            if (abs(rx) < DEADZONE) rx = 0;

            // Forward
            if ((ly > 0) && (lx < 29) && (lx > -29))
            {
                m1.set_direction(LOW);  m1.set_spin(SPEED_MAX);
                m2.set_direction(HIGH); m2.set_spin(SPEED_MAX);
                m3.set_direction(LOW);  m3.set_spin(SPEED_MAX);
                m4.set_direction(HIGH); m4.set_spin(SPEED_MAX);

                Serial.println("Robot Forward");
            }

            // Backward
            else if ((ly < 0) && (lx < 29) && (lx > -29))
            {
                m1.set_direction(HIGH); m1.set_spin(SPEED_MAX);
                m2.set_direction(LOW);  m2.set_spin(SPEED_MAX);
                m3.set_direction(HIGH); m3.set_spin(SPEED_MAX);
                m4.set_direction(LOW);  m4.set_spin(SPEED_MAX);

                Serial.println("Robot Backward");
            }

            // Left
            else if ((lx < 0) && (ly < 29) && (ly > -29))
            {
                m1.set_direction(HIGH); m1.set_spin(SPEED_MAX);
                m2.set_direction(HIGH); m2.set_spin(SPEED_MAX);
                m3.set_direction(LOW);  m3.set_spin(SPEED_MAX);
                m4.set_direction(LOW);  m4.set_spin(SPEED_MAX);

                Serial.println("Robot Left");
            }

            // Right
            else if ((lx > 0) && (ly < 29) && (ly > -29))
            {
                m1.set_direction(LOW);  m1.set_spin(SPEED_MAX);
                m2.set_direction(LOW);  m2.set_spin(SPEED_MAX);
                m3.set_direction(HIGH); m3.set_spin(SPEED_MAX);
                m4.set_direction(HIGH); m4.set_spin(SPEED_MAX);

                Serial.println("Robot Right");
            }

            // Diagonal Top Left
            else if ((ly > 0) && (lx < -30))
            {
                m1.set_direction(LOW);  m1.set_spin(SPEED_MIN);
                m2.set_direction(HIGH); m2.set_spin(SPEED_MAX);
                m3.set_direction(LOW);  m3.set_spin(SPEED_MAX);
                m4.set_direction(HIGH); m4.set_spin(SPEED_MIN);

                Serial.println("Robot Diagonal Top Left!\n");
            }

            // Diagonal Top Right
            else if ((lx > 0) && (ly > 30))
            {
                m1.set_direction(LOW);  m1.set_spin(SPEED_MAX);
                m2.set_direction(HIGH); m2.set_spin(SPEED_MIN);
                m3.set_direction(LOW);  m3.set_spin(SPEED_MIN);
                m4.set_direction(HIGH); m4.set_spin(SPEED_MAX);

                Serial.println("Robot Diagonal Top Right!\n");
            }

            // Diagonal Bottom Right
            else if ((ly < 0) && (lx > 30))
            {
                m1.set_direction(HIGH); m1.set_spin(SPEED_MIN);
                m2.set_direction(LOW);  m2.set_spin(SPEED_MAX);
                m3.set_direction(HIGH); m3.set_spin(SPEED_MAX);
                m4.set_direction(LOW);  m4.set_spin(SPEED_MIN);

                Serial.println("Robot Diagonal Bottom Right!\n");
            }

            // Diagonal Bottom Left
            else if ((lx < 0) && (ly < -30))
            {
                m1.set_direction(HIGH); m1.set_spin(SPEED_MAX);
                m2.set_direction(LOW);  m2.set_spin(SPEED_MIN);
                m3.set_direction(HIGH); m3.set_spin(SPEED_MIN);
                m4.set_direction(LOW);  m4.set_spin(SPEED_MAX);

                Serial.println("Robot Diagonal Bottom Left!\n");
            }

            // Rotate CW
            else if (rx > 45)
            {
                m1.set_direction(LOW);  m1.set_spin(SPEED_MAX);
                m2.set_direction(LOW);  m2.set_spin(SPEED_MAX);
                m3.set_direction(LOW);  m3.set_spin(SPEED_MAX);
                m4.set_direction(LOW);  m4.set_spin(SPEED_MAX);

                Serial.println("Robot Rotate CW");
            }

            // Rotate CCW
            else if (rx < -45)
            {
                m1.set_direction(HIGH); m1.set_spin(SPEED_MAX);
                m2.set_direction(HIGH); m2.set_spin(SPEED_MAX);
                m3.set_direction(HIGH); m3.set_spin(SPEED_MAX);
                m4.set_direction(HIGH); m4.set_spin(SPEED_MAX);

                Serial.println("Robot Rotate CCW");
            }

            // Stop if everything is within deadzone
            else
            {
                m1.set_spin(SPEED_MIN);
                m2.set_spin(SPEED_MIN);
                m3.set_spin(SPEED_MIN);
                m4.set_spin(SPEED_MIN);
                //Serial.println("Robot STOP");
            }
        }
    }
}
#endif
 