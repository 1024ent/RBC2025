/**
 * @file thread_manager.h
 * @brief Spawning applicaton threads
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __THREAD_MANAGER_H__
#define __THREAD_MANAGER_H__

#ifdef MASTER
void master_thread_manager();
#endif

#ifdef SLAVE
void slave_thread_manager();
#endif


#endif