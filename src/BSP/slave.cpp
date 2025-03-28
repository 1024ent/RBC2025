/**
 * @file input_config.cpp
 * @brief Input pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
#include "driver/gpio.h"
#include "driver/uart.h"
#include "sdkconfig.h"
#include "Wire.h"
#include "slave.h"

QueueHandle_t uartQueue;  // FreeRTOS queue for UART data

/**
 * @brief Initialising output instances for master
 */
void slave_init_input_instances() {
    Serial.begin(115200);

    // UART Configuration
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB  // ✅ Fix for PlatformIO
    };

    // Install UART driver with a queue
    uart_driver_install(UART_NUM, 1024, 1024, 10, &uartQueue, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);    
}

/**
 * @brief Initialising output instances for slave
 */
void slave_init_output_instances(){
    /** THREAD INDICATOR **/
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
}

void uart_event_task(void *pvParameters) {
    uart_event_t event;
    uint8_t data[128];

    while (1) {
        if (xQueueReceive(uartQueue, &event, portMAX_DELAY)) {
            if (event.type == UART_DATA) {
                int len = uart_read_bytes(UART_NUM, data, event.size, portMAX_DELAY);
                data[len] = '\0';  // Null-terminate the string
                Serial.print("Received: ");
                Serial.println((char *)data);
            }
        }
    }
}
 