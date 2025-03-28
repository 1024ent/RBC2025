/**
 * @file thread_manager.cpp
 * @brief Spawning application threads
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
#include "driver/gpio.h"
#include "blink_manager.h"
#include "sdkconfig.h"
#include "uart_manager.h"
#include "master.h"
#include "slave.h"

#ifdef MASTER

/** 
 * @brief Task handles for managing different threads 
 */
TaskHandle_t myThreadIndicator = NULL;
TaskHandle_t myUART = NULL;
TaskHandle_t myLogging = NULL;

/**
 * @brief Initializes and creates tasks for concurrent execution.
 * 
 * This function sets up FreeRTOS tasks, assigning them to specific CPU cores 
 * for optimized performance. Tasks will execute according to their assigned priority.
 */
void master_thread_manager()
{
    /**
     * @brief Creating FreeRTOS tasks and assigning them to cores.
     * 
     * @details xTaskCreatePinnedToCore(
     *            TaskFunction_t pvTaskCode,   // Pointer to the function implementing the task
     *            const char *pcName,         // Name of the task (for debugging)
     *            uint32_t usStackDepth,      // Stack size allocated to the task (in words)
     *            void *pvParameters,         // Task parameters (set to NULL if unused)
     *            UBaseType_t uxPriority,     // Task priority (1 = lowest, 15 = highest)
     *            TaskHandle_t *pxCreatedTask,// Handle for the created task
     *            BaseType_t xCoreID          // Core to which the task is pinned (0 or 1)
     *          )
     */

    // Task for blinking an LED to indicate system status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(master_thread_indicator, 
                            "Blinking LED", 
                            2048, 
                            NULL, 
                            1, 
                            NULL, 
                            0);
}
#endif

#ifdef SLAVE
void slave_thread_manager()
{
    /**
     * @brief Creating FreeRTOS tasks and assigning them to cores.
     * 
     * @details xTaskCreatePinnedToCore(
     *            TaskFunction_t pvTaskCode,   // Pointer to the function implementing the task
     *            const char *pcName,         // Name of the task (for debugging)
     *            uint32_t usStackDepth,      // Stack size allocated to the task (in words)
     *            void *pvParameters,         // Task parameters (set to NULL if unused)
     *            UBaseType_t uxPriority,     // Task priority (1 = lowest, 15 = highest)
     *            TaskHandle_t *pxCreatedTask,// Handle for the created task
     *            BaseType_t xCoreID          // Core to which the task is pinned (0 or 1)
     *          )
     */

    // Task for blinking an LED to indicate system status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(slave_thread_indicator, 
                            "Blinking LED", 
                            2048, 
                            NULL, 
                            1, 
                            NULL, 
                            0);

    // // Task for blinking an LED to indicate system status (Runs on Core 0 with low priority)
    // xTaskCreatePinnedToCore(send_and_parse_value, 
    //     "Connecting to UART ...", 
    //     8192, 
    //     NULL, 
    //     tskIDLE_PRIORITY, 
    //     &myUART, 
    //     1);

    // Task for blinking an LED to indicate system status (Runs on Core 0 with low priority)
    // xTaskCreatePinnedToCore(parse_value, 
    //     "Logging current status", 
    //     8192, 
    //     NULL, 
    //     1, 
    //     &myLogging, 
    //     1);
}
#endif
