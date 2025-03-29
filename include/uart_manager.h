/**
 * @file uart_manager.h
 * @brief Managing PS4 buttons to Microcontroller through UART
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __UART_MANAGER_H__
#define __UART_MANAGER_H__ 

#include <Arduino.h>
#include <PS4Controller.h>

class ps4_buttons {
private:
    int tx_pin;
    int rx_pin;

public:
    void uart_init(int tx_buf, int rx_buf) {
        tx_pin = tx_buf;
        rx_pin = rx_buf;
        Serial2.begin(115200, SERIAL_8N1, tx_pin, rx_pin);
    }

    void send_btns(int btn_val) {
        Serial.printf("[UART] BTN SENT: %d\n", btn_val);
        Serial2.println(btn_val);
    }
};

#ifdef MASTER
void send_and_parse_value(void *parameter);
#endif

#ifdef SLAVE
// Global variables declaration
extern int lStickX;
extern int lStickY;
extern int buttonValue;
void uart_receive_task(void *parameter);
#endif

#endif