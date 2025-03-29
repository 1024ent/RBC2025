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
     * @brief Parsing values from buttons and send to STM32 through UART
     */
    void send_and_parse_value(void *parameter) {
        ps4_buttons btn;
        btn.uart_init(TX2, RX2);

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
                if (shareButtonPressed == 1)
                {
                }
                else if (optionsButtonPressed == 1)
                {
                }
            }
        }
    }

    void parse_value(void *parameter) {
        for (;;)
        {
            if (Serial2.available())
            {
                int receivedValue = Serial2.parseInt();
                Serial.printf("[UART_MANAGER] Mechanism running STM32 MB : %d\n", receivedValue);
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
#endif

#ifdef SLAVE

#endif
