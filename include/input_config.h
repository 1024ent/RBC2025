/**
 * @file input_config.h
 * @brief Input pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __INPUT_CONFIG_H__
#define __INPUT_CONFIG_H__

#ifdef MASTER

#define PS4_MAC_ADDRESS "d8:bc:38:fc:9f:ba"
// 14:2b:2f:c0:28:fe

void master_init_input_instances();

#endif

#ifdef SLAVE
/** DRIBBLING MECHANISM **/
// BALL PICKING MECHANISM
#define     LIM_Z1   GPIO_NUM_15
#define     LIM_Z2   GPIO_NUM_4
#define     LIM_Y1   GPIO_NUM_33
#define     LIM_Y2   GPIO_NUM_21


void slave_init_input_instances();

#endif

#endif 
