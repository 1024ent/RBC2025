/**
 * @file mdd10a.cpp
 * @brief Managing MDD10A behaviour
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Kishan Kumar [ELPROG]
 */

#include "mdd10a.h"
#include "output_config.h"

#define SPEED_MAX 65535
#define SPEED_MID 20000
#define SPEED_MIN 0

motor m1;

void init_mdd10a_instances()
{
    m1.init_data(MOTOR5_PWM, MOTOR5_DIR);
}

void mdd10a_open()
{
    m1.set_direction(LOW);
    m1.set_spin(SPEED_MAX);
}

void mdd10a_close()
{
    m1.set_direction(HIGH);
    m1.set_spin(SPEED_MAX);
}

void mdd10a_none()
{
    m1.set_spin(SPEED_MIN);
}

void mdd10a_man_move_cw()
{
    m1.man_move(HIGH, SPEED_MID);
}

void mdd10a_man_move_ccw()
{
    m1.man_move(LOW, SPEED_MID);
}

void mdd10a_man_move_none()
{
    m1.man_move(LOW, SPEED_MIN);
}