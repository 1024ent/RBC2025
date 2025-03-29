/**
 * @file uart_manager.cpp
 * @brief Sending PS4 buttons to Microcontroller through UART
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 */

#include "uart_manager.h"
#include "output_config.h"

/**
     JOYSTICK TABLE
==================================
|BUTTONS | VALUE |  MECHANISM    |
==================================
|  RIGHT |   1   |     TBC       |
|  DOWN  |   2   |     TBC       |
|  UP    |   3   |     TBC       |
| LEFT   |   4   |     TBC       |
| SQUARE |   5   |     TBC       |
| CROSS  |   6   |     TBC       |
| CIRCLE |   7   |     TBC       |
|TRIANGLE|   8   |     TBC       |
|   L1   |   9   |     TBC       |
|   R1   |   10  |     TBC       |
|   L2   | pwm-- |  ROBOT BASE   |
|   R2   | pwm++ |  ROBOT BASE   |
|   L3   |  TBC  |     TBC       |
|   R3   |  TBC  |     TBC       |
|  L JOY | dir   |  ROBOT BASE   |
|  R JOY | dir   |  ROBOT BASE   |
|  SHARE |ACTIVE | MOTOR ACTIVATE|
| OPTIONS|  TBC  |     TBC       |
|TOUCHPAD|  TBC  |     TBC       |
==================================
*/

#ifdef MASTER
    /**
     * @brief Parsing values from buttons and send to ESP32 Slave Board through UART 
     */
    void send_and_parse_value(void *parameter) {
        ps4_buttons btn;
        btn.uart_init(UART2_TX_PIN, UART2_RX_PIN);

        bool shareButtonPressed = false;
        bool optionsButtonPressed = false;

        for (;;)
        {
            if (PS4.isConnected())
            {
                if (PS4.Right())
                    btn.send_btns(1);
                if (PS4.Down())
                    btn.send_btns(2);
                if (PS4.Up())
                    btn.send_btns(3);
                if (PS4.Left())
                    btn.send_btns(4);
                if (PS4.Square())
                    btn.send_btns(5);
                if (PS4.Cross())
                    btn.send_btns(6);
                if (PS4.Circle())
                    btn.send_btns(7);
                if (PS4.Triangle())
                    btn.send_btns(8);
                if (PS4.L1())
                    btn.send_btns(9);
                if (PS4.R1())
                    btn.send_btns(10);
                if (PS4.L2())
                {
                    Serial.printf("L2 button at %d\n", PS4.L2Value());
                }
                if (PS4.L3())
                    Serial.println("L3 Button");
                if (PS4.R3())
                    Serial.println("R3 Button");
                if (PS4.Touchpad())
                    Serial.println("Touch Pad Button");
                if (PS4.Share())
                {
                    shareButtonPressed = true;
                    optionsButtonPressed = false;
                    Serial.printf("[UART_MANAGER] : MOTORS ACTIVATED!\n");
                }
                if (PS4.Options())
                {
                    shareButtonPressed = false;
                    optionsButtonPressed = true;
                }
                if (shareButtonPressed)
                {
                    // Add logic here if needed
                }
                else if (optionsButtonPressed)
                {
                    // Add logic here if needed
                }

                // Send analog stick values
                int lx = PS4.LStickX();
                int ly = PS4.LStickY();
                Serial2.printf("LX:%d\n", lx);
                Serial2.printf("LY:%d\n", ly);
                
                Serial.printf("[MASTER] SENT LX:%d LY:%d\n", lx, ly);
            }
            vTaskDelay(pdMS_TO_TICKS(50));  // Small delay to avoid flooding UART
        }
    }
#endif

#ifdef SLAVE
#include "uart_manager.h"
#include "output_config.h"

// Global variables definition
int LStickX = 0;
int LStickY = 0;
int buttonValue = 0;

void uart_receive_task(void *parameter) {
    Serial2.begin(115200, SERIAL_8N1, UART2_RX_PIN, UART2_TX_PIN);
    char receivedData[32];  // Increased buffer size
    int index = 0;

    for (;;) {
        while (Serial2.available() > 0) {
            char incomingByte = Serial2.read();

            if (incomingByte == '\n') {
                receivedData[index] = '\0';
                
                // Parse LX values
                if (strncmp(receivedData, "LX:", 3) == 0) {
                    LStickX = atoi(receivedData + 3);
                    Serial.printf("[UART] LX: %d\n", LStickX);
                }
                // Parse LY values
                else if (strncmp(receivedData, "LY:", 3) == 0) {
                    LStickY = atoi(receivedData + 3);
                    Serial.printf("[UART] LY: %d\n", LStickY);
                }
                // Parse button values (simple integers)
                else {
                    buttonValue = atoi(receivedData);
                    if (buttonValue != 0) {  // Filter out accidental zeros
                        Serial.printf("[UART] BTN: %d\n", buttonValue);
                    }
                }
                
                index = 0;  // Reset buffer
            } else {
                if (index < sizeof(receivedData) - 1) {
                    receivedData[index++] = incomingByte;
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
#endif
