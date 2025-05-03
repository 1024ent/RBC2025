/**
 * @file robot_movement.h
 * @brief Controlling robot movement through PS4 Controllers
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __ROBOTMOVEMENT_H__
#define __ROBOTMOVEMENT_H__

#include <Arduino.h>
#include "PS4Controller.h"
class motor {
private:
    int digital_pin;
    int analog_pin;
    int channel_num;
    int direction;
    int pwm_val;
    float pwm_val_smooth = 0;
    float pwm_val_prev = 0;

public:
    void init_data(int dig, int ana, int channel)
    {
        digital_pin = dig;
        analog_pin = ana;
        channel_num = channel;

        pinMode(digital_pin, OUTPUT);
        ledcAttachPin(analog_pin, channel_num);
        ledcSetup(channel_num, 20000, 8); // 20 kHz, 8-bit PWM
    }

    void set_direction(int dir) {
        direction = dir;
        digitalWrite(digital_pin, dir);
    }

    void set_spin(int pwm)
    {
        pwm_val = constrain(pwm, 0, 255);
        pwm_val_smooth = pwm_val * 0.1f + pwm_val_prev * 0.9f;
        pwm_val_prev = pwm_val_smooth;
        ledcWrite(channel_num, pwm_val_smooth);
    }

    void move(int dir, int pwm) {
        set_direction(dir);
        set_spin(pwm);
    }
};

void robot_movement_omni(void *parameter);

#endif
