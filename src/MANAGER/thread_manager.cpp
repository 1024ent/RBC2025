/**
 * @file thread_manager.cpp
 * @brief Spawning application threads
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
#include "driver/gpio.h"
#include "blink_manager.h"
#include "sdkconfig.h"
#include "uart_manager.h"

#ifdef MASTER
#include "robot_movement.h"
#include "controller_manager.h"
/** 
 * @brief Task handles for managing different threads 
 */
TaskHandle_t myThreadIndicator = NULL;
TaskHandle_t myLogging = NULL;
TaskHandle_t myController = NULL;
TaskHandle_t myControllerLed = NULL;
TaskHandle_t myMovement = NULL;

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

    // Task for blinking an LED to indicate system status 
    xTaskCreatePinnedToCore(master_thread_indicator, 
                            "Blinking LED", 
                            1024, 
                            NULL, 
                            1, 
                            &myThreadIndicator, 
                            0);
    
    // Task for blinking an LED to indicate system status 
    xTaskCreatePinnedToCore(controller_manager, 
                            "Managing controller", 
                            4096, 
                            NULL, 
                            3, 
                            &myController, 
                            0);
    
    // Task for blinking an LED to indicate system status 
    xTaskCreatePinnedToCore(controller_led_sequence, 
                            "Managing controller led sequence", 
                            4096, 
                            NULL, 
                            1, 
                            &myControllerLed, 
                            0);

    // Task for blinking an LED to indicate system status 
    xTaskCreatePinnedToCore(send_and_parse_value, 
                            "Connecting to UART ...", 
                            10000, 
                            NULL, 
                            3, 
                            &myLogging, 
                            0); 

    // Task for blinking an LED to indicate system status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(robot_movement_omni_v2, 
                            "Connecting to base ...", 
                            75000, 
                            NULL, 
                            2, 
                            &myMovement, 
                            1);
}
#endif

#ifdef SLAVE
#include "dribbling.h"
#include "shooting.h"
TaskHandle_t myUART = NULL;

void slave_thread_manager() {
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

    // Task for receiving and parsing UART data (Runs on Core 0 with high priority)
    xTaskCreatePinnedToCore(uart_receive_task, 
                            "Receiving UART TASK ...", 
                            10000, 
                            NULL, 
                            5, 
                            &myUART, 
                            0);

    // Task for SHOOTING MECHANISM status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(shooting_mechanism, 
                            "Running Shooting Mechanism ...", 
                            4096, 
                            NULL, 
                            3, 
                            NULL, 
                            1);
                            
    // Task for DRIBBLING MECHANISM status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(dribbling_mechanism, 
                            "Running Dribbling Mechanism ...", 
                            4096, 
                            NULL, 
                            3, 
                            NULL, 
                            1); 

    // Task for LIFTING MECHANISM status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(lifting_mechanism, 
                            "Running Lifting Mechanism ...", 
                            4096, 
                            NULL, 
                            3, 
                            NULL, 
                            1);

    // Task for LOWERING MECHANISM status (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(lowering_mechanism, 
                            "Running Lowering Mechanism ...", 
                            4096, 
                            NULL, 
                            3, 
                            NULL, 
                            1);     
    
    // Task for Yaw Forward Mechanism (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(yaw_forward_mechanism,      
                            "Running Yaw Forward Mechanism ...", 
                            4096, 
                            NULL, 
                            3, 
                            NULL, 
                            1); 
    
    // Task for Yaw Backward Mechanism (Runs on Core 0 with low priority)
    xTaskCreatePinnedToCore(yaw_backward_mechanism,      
                            "Running Yaw Backward Mechanism ...", 
                            4096, 
                            NULL, 
                            3, 
                            NULL, 
                            1); 
}
#endif
