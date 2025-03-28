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
/** INPUT PINS DECLARATION */
#define PS4_MAC_ADDRESS "14:2b:2f:c0:28:fe"

void master_init_input_instances();
#endif

#ifdef SLAVE
void slave_init_input_instances();
#endif

#endif