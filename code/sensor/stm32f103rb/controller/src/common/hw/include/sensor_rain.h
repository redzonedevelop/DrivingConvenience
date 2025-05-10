/*
 * sensor_rain.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_COMMON_HW_INCLUDE_SENSOR_RAIN_H_
#define SRC_COMMON_HW_INCLUDE_SENSOR_RAIN_H_

#include "hw_def.h"

#ifdef _USE_HW_RAIN

void sensor_rain_init();
void set_sensor_rain();
bool get_sensor_rain();

#endif
#endif
