/**
 * @file master.h
 * @brief header file for master.cpp
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __MASTER_H__
#define __MASTER_H__

#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM UART_NUM_2  // Using UART2
#define TXD_PIN 17           // Master TX -> Slave RX
#define RXD_PIN 16           // (Not used in Master)

#define BLINK_GPIO1 GPIO_NUM_2

/** INPUT PINS DECLARATION */
#define PS4_MAC_ADDRESS "14:2b:2f:c0:28:fe"

void master_init_input_instances();
void master_init_output_instances();
void sendTask(void *pvParameters);

#endif 