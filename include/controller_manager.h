/**
 * @file controller_manager.h
 * @brief Managing PS4 Controller Information
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Nazwa Najmuddin [ELPROG]
 */

#ifndef __CONTROLLER_MANAGER_H__
#define __CONTROLLER_MANAGER_H__

#ifdef MASTER
void controller_manager(void *pvParameters);
void controller_led_sequence(void *pvParameters);
#endif

#ifdef SLAVE

#endif

#endif