/*
 * sensor_rain.c
 *
 *  Created on: May 11, 2025
 *      Author: USER
 */

#include "sensor.h"



void set_sensor_rain(){
	if (!sensor_info.error_flag.rain_error)
		sensor_info.sensor_value.rain = gpio_pin_read(_DEF_GPIO2);
}

bool get_sensor_rain(){
   return sensor_info.sensor_value.rain;
}
