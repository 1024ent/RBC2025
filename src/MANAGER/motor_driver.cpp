/**
 * @file input_config.h
 * @brief Input pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Al Imran [ELPROG]
 */
#include "motor_driver.h"

MD::MD(MODE mode, uint8_t pin1, uint8_t pin2)
  : _mode(mode), _pin1(pin1), _pin2(pin2)
{
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
}

void MD::setSpeed(int16_t speed)
{
  if (_mode == PWM_DIR)
  {
    bool dir = speed >= 0;
    analogWrite(_pin1, abs(speed));   // PWM
    digitalWrite(_pin2, dir);         // Direction
  }
  else if (_mode == PWM_PWM)
  {
    if (speed > 0)
    {
      analogWrite(_pin1, speed);
      analogWrite(_pin2, 0);
    }
    else if (speed < 0)
    {
      analogWrite(_pin1, 0);
      analogWrite(_pin2, abs(speed));
    }
    else
    {
      analogWrite(_pin1, 0);
      analogWrite(_pin2, 0);
    }
  }
}
