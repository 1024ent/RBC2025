/**
 * @file slaveh
 * @brief header file for slave.cpp
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __SLAVE_H__
#define __SLAVE_H__

#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM UART_NUM_2  // Using UART2
#define TXD_PIN 17           // Master TX -> Slave RX
#define RXD_PIN 16           // (Not used in Master)

#define BLINK_GPIO1 GPIO_NUM_2

void slave_init_input_instances();
void slave_init_output_instances();
void uart_event_task(void *pvParameters);

#endif 