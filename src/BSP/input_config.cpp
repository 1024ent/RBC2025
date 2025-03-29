/**
 * @file input_config.cpp
 * @brief Input pins instances configuration
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#include <Arduino.h>
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "input_config.h"
#include "Wire.h"
#include "PS4Controller.h"

#ifdef MASTER
/**
 * @brief Initialising output instances for master
 */
void master_init_input_instances() {
    /** PS4 CONTROLLER **/
    PS4.begin(PS4_MAC_ADDRESS);
}
#endif

#ifdef SLAVE
/**
 * @brief Initialising output instances for slave
 */
void slave_init_input_instances() {

}
#endif
 

 


