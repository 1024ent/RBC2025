/**
 * @file main.cpp
 * @brief Master & Slave ESP32 Main Program
 * @copyright UMPSA ROBOTICS
 * @license Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
// #include "input_config.h"   // Handles input configurations
// #include "output_config.h"  // Handles output configurations
#include "thread_manager.h" // Manages task/thread execution
// #include "uart_manager.h"   // Manages UART communication

#ifdef MASTER
#include "master.h"  // Uncomment if additional master-specific code is needed

/**
 * @brief Master MCU Setup Function
 * This function initializes the serial communication, input instances,
 * output instances, and starts the thread manager for multi-threaded execution.
 */
void setup() {
    master_init_input_instances();  // Initialize input configurations for Master
    master_init_output_instances(); // Initialize output configurations for Master

    master_thread_manager(); // Start the thread/task manager
}

/**
 * @brief Master MCU Loop Function
 * Currently empty since the logic is managed by the thread manager.
 */
void loop() {
    // Master-specific loop code (if required in the future)
}
#endif

#ifdef SLAVE
#include "slave.h"  // Uncomment if additional slave-specific code is needed

/**
 * @brief Slave MCU Setup Function
 * This function initializes the serial communication and input instances.
 */
void setup() {
    slave_init_input_instances(); // Initialize input configurations for Slave
    slave_init_output_instances(); // Initialize output configurations for Slave

    slave_thread_manager(); // Start the thread/task manager
}

/**
 * @brief Slave MCU Loop Function
 * Currently empty since the logic is managed by other configurations.
 */
void loop() {
    // Slave-specific loop code (if required in the future)
}
#endif

 