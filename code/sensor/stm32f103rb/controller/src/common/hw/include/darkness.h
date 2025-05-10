/*
 * darkness.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_COMMON_HW_INCLUDE_DARKNESS_H_
#define SRC_COMMON_HW_INCLUDE_DARKNESS_H_


#include "hw_def.h"

#ifdef _USE_HW_DARKNESS

bool darkness_init();
void set_sensor_darkness();
bool get_sensor_darkness();
void set_mode_darkness();
void get_mode_darkness();
void compare_mode_darkness();

#endif
#endif
