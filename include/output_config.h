/**
 * @file output_config.h
 * @brief Output pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __OUTPUT_CONFIG_H__
#define __OUTPUT_CONFIG_H__

#include "driver/gpio.h"

#ifdef MASTER
/** THREAD INDICATOR **/
#define     BLINK_GPIO1         GPIO_NUM_2

#define PS4_MAC_ADDRESS "14:2b:2f:c0:28:fe"
void master_init_output_instances();

#endif

#ifdef SLAVE
/** THREAD INDICATOR **/
#define     BLINK_GPIO1         GPIO_NUM_2

/** ROBOT BASE OUTPUT PINS **/
#define     MOTOR1_PWM          GPIO_NUM_25
#define     MOTOR1_DIR          GPIO_NUM_26

#define     MOTOR2_PWM          GPIO_NUM_27
#define     MOTOR2_DIR          GPIO_NUM_14

#define     MOTOR3_PWM          GPIO_NUM_32
#define     MOTOR3_DIR          GPIO_NUM_33

#define     MOTOR4_PWM          GPIO_NUM_4
#define     MOTOR4_DIR          GPIO_NUM_5

/** MDD10A TEST **/
#define     MOTOR5_PWM          GPIO_NUM_19
#define     MOTOR5_DIR          GPIO_NUM_21

void slave_init_output_instances();

#endif

#endif
 