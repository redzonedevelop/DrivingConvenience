/*
 * sensor_rain.h
 *
 *  Created on: May 11, 2025
 *      Author: USER
 */

#ifndef SRC_AP_CORE_SENSOR_SENSOR_RAIN_H_
#define SRC_AP_CORE_SENSOR_SENSOR_RAIN_H_

#include "ap_def.h"

#define STM_TRANS		0
#define STM_CONTROLLER	1
#define STM_SUBORDINATE	2

void set_speed(int count);
int get_speed();

void set_steering_angle(int count);
int get_steering_angle();

void set_sensor_brightness(int count);
int get_sensor_brightness();

void set_sensor_darkness(int count);
bool get_sensor_darkness();

void set_esp32();

void set_sensor_rain(int count);
bool get_sensor_rain();

#endif /* SRC_AP_CORE_SENSOR_SENSOR_RAIN_H_ */
