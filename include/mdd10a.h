/**
 * @file mdd10a.cpp
 * @brief Managing MDD10A behaviour
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 */

#include <Arduino.h>

class motor
{
private:
    int digital_pin;
    int analog_pin;
    int direction;
    int pwm_val;
    float pwm_val_smooth;
    float pwm_val_prev;

public:
    void init_data(int dig, int ana)
    {
        digital_pin = dig;
        analog_pin = ana;

        pinMode(digital_pin, OUTPUT);
    }

    float speed_control()
    {
        pwm_val_smooth = (pwm_val * 0.06) + (pwm_val_prev * 0.94);
        pwm_val_prev = pwm_val_smooth;
        return pwm_val_smooth;
    }

    void set_spin(int pwm)
    {
        unsigned long time_now = millis();
        int delay_period = 200;
        pwm_val = pwm;

        while (millis() < time_now + delay_period)
        {
            float new_pwm = speed_control();
            Serial.println(new_pwm);
            digitalWrite(digital_pin, direction);
            analogWrite(analog_pin, new_pwm);
        }
    }

    void set_direction(int dir)
    {
        direction = dir;
    }

    void man_move(int dir, int speed)
    {
        direction = dir;
        digitalWrite(digital_pin, direction);
        analogWrite(analog_pin, speed);
        Serial.println(speed);
    }
};

void init_mdd10a_instances();
void mdd10a_open();
void mdd10a_close();
void mdd10a_none();
void mdd10a_man_move_cw();
void mdd10a_man_move_ccw();
void mdd10a_man_move_none();