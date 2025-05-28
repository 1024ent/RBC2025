/**
 * @file dribbling.cpp
 * @brief Managing Dribbling Mechanism
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Al-Imran [ELPROG]
 * @author Khairuddin [ELPROG]
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __DRIBBLING_H__
#define __DRIBBLING_H__

#ifdef SLAVE
void dribbling_mechanism(void *parameter);
void lifting_mechanism(void *parameter);
void lowering_mechanism(void *parameter);
void yaw_forward_mechanism(void *parameter);
void yaw_backward_mechanism(void *parameter);
void ball_picking_mechanism(void *parameter);   // Semi-auto ball picking mechanism function

#endif

#endif