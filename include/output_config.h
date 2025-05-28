/**
 * @file output_config.h
 * @brief Output pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __OUTPUT_CONFIG_H__
#define __OUTPUT_CONFIG_H__

#include "driver/gpio.h"

#ifdef MASTER
/** THREAD INDICATOR **/
#define     BLINK_GPIO1         GPIO_NUM_2

/** UART2 | Serving: ESP32 SLAVE BOARD **/
#define     UART2_TX_PIN        GPIO_NUM_16
#define     UART2_RX_PIN        GPIO_NUM_17

/** ROBOT BASE OUTPUT PINS **/
#define     MOTOR1_PWM          GPIO_NUM_26
#define     MOTOR1_DIR          GPIO_NUM_25

#define     MOTOR2_PWM          GPIO_NUM_27
#define     MOTOR2_DIR          GPIO_NUM_14

#define     MOTOR3_PWM          GPIO_NUM_32
#define     MOTOR3_DIR          GPIO_NUM_33
          
#define     MOTOR4_PWM          GPIO_NUM_4
#define     MOTOR4_DIR          GPIO_NUM_23

void master_init_output_instances();

#endif

#ifdef SLAVE
/** THREAD INDICATOR **/
#define     BLINK_GPIO1         GPIO_NUM_2

/** SHOOTING MECHANISM **/
#define     SHOOT_PWM_L         GPIO_NUM_12
#define     SHOOT_DIR_L         GPIO_NUM_13
#define     SHOOT_PWM_R         GPIO_NUM_26 
#define     SHOOT_DIR_R         GPIO_NUM_19 
#define     SHOOT_RELAY         GPIO_NUM_5

/** DRIBBLING MECHANISM **/
// BALL PICKING MECHANISM
#define     PICK_PWM_Z         GPIO_NUM_18
#define     PICK_DIR_Z         GPIO_NUM_25
#define     PICK_PWM_Y         GPIO_NUM_14
#define     PICK_DIR_Y         GPIO_NUM_27

// BALL DRIBBLING MECHANISM
#define     RELAY1_PIN          GPIO_NUM_26  // GPIO 26 connected to Relay 1
#define     RELAY2_PIN          GPIO_NUM_27

/** UART2 | Receiving: ESP32 MB **/
#define UART2_TX_PIN GPIO_NUM_17  
#define UART2_RX_PIN GPIO_NUM_16  

void slave_init_output_instances();

#endif

#endif
