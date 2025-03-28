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
#include "PS4Controller.h"
#include "master.h"

/**
 * @brief Initialising output instances for master
 */
void master_init_input_instances() {
    Serial.begin(115200);

    /** PS4 CONTROLLER **/
    PS4.begin(PS4_MAC_ADDRESS);

    // UART Configuration
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB
    };

    // Install UART driver
    uart_driver_install(UART_NUM, 1024, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);    
}

/**
 * @brief Initialising output instances for slave
 */
void master_init_output_instances(){
    /** THREAD INDICATOR **/
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
}

void sendTask(void *pvParameters) {
    while (1) {
        const char *message = "Hello from Master!\n";
        uart_write_bytes(UART_NUM, message, strlen(message));  // Send data
        Serial.println("Sent: Hello from Master!");
        vTaskDelay(pdMS_TO_TICKS(500));  // Delay 500ms
    }
}
