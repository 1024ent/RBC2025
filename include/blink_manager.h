/**
 * @file blink_manager.h
 * @brief Managing thread indicator
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __BLINK_MANAGER_H__
#define __BLINK_MANAGER_H__

void master_thread_indicator(void *pvParameters);
void slave_thread_indicator(void *pvParameters);

#endif