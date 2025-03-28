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

#define SPEED_MAX 255
#define SPEED_MID 200
#define SPEED_MIN 0

#ifdef SLAVE
void robot_movement_mecanum(void *parameter)
{
    bool shareButtonPressed = false;
    bool optionsButtonPressed = false;

    ps4_buttons btn;
    motor m1;
    motor m2;
    motor m3;
    motor m4;

    btn.uart_init(TX2, RX2);
    m1.init_data(MOTOR1_DIR, MOTOR1_PWM, 0);
    m2.init_data(MOTOR2_DIR, MOTOR3_PWM, 1);
    m3.init_data(MOTOR3_DIR, MOTOR3_DIR, 2);
    m4.init_data(MOTOR4_DIR, MOTOR4_DIR, 3);

    for (;;)
    {

        if (PS4.isConnected())
        {
            if ((PS4.LStickY() > 10) && (PS4.LStickX() < 34) && (PS4.LStickX() > -34))
            {
                m1.set_direction(HIGH);
                m1.set_spin(SPEED_MID);
                m2.set_direction(LOW);
                m2.set_spin(SPEED_MID);
                m3.set_direction(HIGH);
                m3.set_spin(SPEED_MID);
                m4.set_direction(HIGH);
                m4.set_spin(SPEED_MID);
                Serial.println("Robot Forward");
            }

            if ((PS4.LStickY() < -10) && (PS4.LStickX() < 34) && (PS4.LStickX() > -34))
            {
                m1.set_direction(LOW);
                m1.set_spin(SPEED_MID);
                m2.set_direction(HIGH);
                m2.set_spin(SPEED_MID);
                m3.set_direction(LOW);
                m3.set_spin(SPEED_MID);
                m4.set_direction(LOW);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Backward");
            }

            if ((PS4.LStickX() < -10) && (PS4.LStickY() < 34) && (PS4.LStickY() > -34))
            {
                m1.set_direction(HIGH);
                m1.set_spin(SPEED_MID);
                m2.set_direction(HIGH);
                m2.set_spin(SPEED_MID);
                m3.set_direction(HIGH);
                m3.set_spin(SPEED_MID);
                m4.set_direction(LOW);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Left");
            }

            if ((PS4.LStickX() > 10) && (PS4.LStickY() < 34) && (PS4.LStickY() > -34))
            {
                m1.set_direction(LOW);
                m1.set_spin(SPEED_MID);
                m2.set_direction(LOW);
                m2.set_spin(SPEED_MID);
                m3.set_direction(LOW);
                m3.set_spin(SPEED_MID);
                m4.set_direction(HIGH);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Right");
            }

            if ((PS4.LStickY() > 10) && (PS4.LStickX() < -35) && (PS4.LStickX() > -132))
            {
                m1.set_direction(HIGH);
                m1.set_spin(SPEED_MIN);
                m2.set_direction(LOW);
                m2.set_spin(SPEED_MID);
                m3.set_direction(LOW);
                m3.set_spin(SPEED_MIN);
                m4.set_direction(HIGH);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Diagonal Top Left!\n");
            }

            if ((PS4.LStickX() > 10) && (PS4.LStickY() < 132) && (PS4.LStickY() > 35))
            {
                m1.set_direction(HIGH);
                m1.set_spin(SPEED_MID);
                m2.set_direction(LOW);
                m2.set_spin(SPEED_MIN);
                m3.set_direction(HIGH);
                m3.set_spin(SPEED_MID);
                m4.set_direction(HIGH);
                m4.set_spin(SPEED_MIN);

                Serial.println("Robot Diagonal Top Right!\n");
            }

            if ((PS4.LStickY() < -10) && (PS4.LStickX() < 132) && (PS4.LStickX() > 35))
            {
                m1.set_direction(LOW);
                m1.set_spin(SPEED_MIN);
                m2.set_direction(HIGH);
                m2.set_spin(SPEED_MID);
                m3.set_direction(HIGH);
                m3.set_spin(SPEED_MIN);
                m4.set_direction(LOW);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Diagonal Bottom Right!\n");
            }

            if ((PS4.LStickX() < -10) && (PS4.LStickY() < -35) && (PS4.LStickY() > -132))
            {
                m1.set_direction(LOW);
                m1.set_spin(SPEED_MID);
                m2.set_direction(HIGH);
                m2.set_spin(SPEED_MIN);
                m3.set_direction(LOW);
                m3.set_spin(SPEED_MID);
                m4.set_direction(LOW);
                m4.set_spin(SPEED_MIN);
                Serial.println("Robot Diagonal Bottom Left!\n");
            }

            if (PS4.RStickX() > 50)
            {
                m1.set_direction(LOW);
                m1.set_spin(SPEED_MID);
                m2.set_direction(LOW);
                m2.set_spin(SPEED_MID);
                m3.set_direction(HIGH);
                m3.set_spin(SPEED_MID);
                m4.set_direction(LOW);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Rotate CW");
            }

            if (PS4.RStickX() < -50)
            {

                m1.set_direction(HIGH);
                m1.set_spin(SPEED_MID);
                m2.set_direction(HIGH);
                m2.set_spin(SPEED_MID);
                m3.set_direction(LOW);
                m3.set_spin(SPEED_MID);
                m4.set_direction(HIGH);
                m4.set_spin(SPEED_MID);

                Serial.println("Robot Rotate CCW");
            }

            if (PS4.Right())
                btn.send_btns(1);
            if (PS4.Down())
                btn.send_btns(2);
            if (PS4.Up())
                btn.send_btns(3);
            if (PS4.Left())
                btn.send_btns(4);
            if (PS4.Square())
                btn.send_btns(5);
            if (PS4.Cross())
                btn.send_btns(6);
            if (PS4.Circle())
                btn.send_btns(7);
            if (PS4.Triangle())
                btn.send_btns(8);
            if (PS4.L1())
                btn.send_btns(9);
            if (PS4.R1())
                btn.send_btns(10);
            if (PS4.L2())
                Serial.printf("L2 button at %d\n", PS4.L2Value());
            if (PS4.L3())
                Serial.println("L3 Button");
            if (PS4.R3())
                Serial.println("R3 Button");
            if (PS4.Touchpad())
                Serial.println("Touch Pad Button");
            if (PS4.Share())
            {
                shareButtonPressed = true;
                optionsButtonPressed = false;
                Serial.printf("[UART_MANAGER] : MOTORS ACTIVATED!\n");
            }
            if (PS4.Options())
            {
                shareButtonPressed = false;
                optionsButtonPressed = true;
            }
            if (shareButtonPressed == 1)
            {
            }
            if (optionsButtonPressed == 1)
            {
            }

            else
            {
                m1.set_spin(SPEED_MIN);
                m2.set_spin(SPEED_MIN);
                m3.set_spin(SPEED_MIN);
                m4.set_spin(SPEED_MIN);
                // Serial.println("Robot STOP");
            }
        }
    }
}
#endif
