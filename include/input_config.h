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
#define PS4_MAC_ADDRESS "a8:42:e3:8f:fa:06"
void master_init_input_instances();
#endif

#ifdef SLAVE
void slave_init_input_instances();
#endif

#endif // __INPUT_CONFIG_H__
