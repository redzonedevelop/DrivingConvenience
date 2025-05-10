/*
 * rain.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_COMMON_HW_INCLUDE_RAIN_H_
#define SRC_COMMON_HW_INCLUDE_RAIN_H_


#include "hw_def.h"

#ifdef _USE_HW_RAIN

bool rain_init(void);
void set_sensor_rain(void);
void get_sensor_rain(void);
void set_mode_rain(void);
void get_mode_rain(void);
void compare_mode_rain(void);

#endif
#endif
