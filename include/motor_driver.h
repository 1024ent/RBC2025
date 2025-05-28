/**
 * @file input_config.h
 * @brief Input pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>
#include <stdint.h>

enum MODE {
  PWM_DIR,
  PWM_PWM,
};

class MD
{
  public:
    MD(MODE mode, uint8_t pin1, uint8_t pin2);
    void setSpeed(int16_t speed);
    
  protected:
    MODE _mode;
  	uint8_t _pin1;
    uint8_t _pin2;
};

/* class MD10C : public CytronMD
{
  public:
    MD10C(uint8_t pwmPin, uint8_t dirPin) : MD(PWM_DIR, pwmPin, dirPin) {};
};

class MD13S : public CytronMD
{
  public:
    MD13S(uint8_t pwmPin, uint8_t dirPin) : MD(PWM_DIR, pwmPin, dirPin) {};
}; */

#endif