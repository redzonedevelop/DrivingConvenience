/*
 * ap_def.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_AP_DEF_H_
#define SRC_AP_AP_DEF_H_

#include "hw.h"



typedef struct
{
   uint16_t speed;
   int16_t  steering_angle;
} car_value_t;

typedef struct
{
   uint16_t brightness;
   uint16_t darkness;
   uint16_t humidity;
   bool rain;
} sensor_value_t;

typedef struct
{
   bool brightness_error;
   bool darkness_error;
   bool humidity_error;
   bool rain_error;
} error_t;

typedef struct
{
   uint8_t mode_auto;
   uint8_t mode_driving;
   uint8_t mode_high_beam;
   uint8_t mode_rain_road;
   uint8_t mode_corner_light;
   uint8_t mode_fog_light;
   uint8_t mode_seat;
} mode_t;

typedef struct
{
   car_value_t car_value[4];
   sensor_value_t sensor_value[4];
   error_t error_flag;
   mode_t mode[3];
} sensor_controller_t;

typedef struct
{
	uint16_t	speed;
	int16_t		steering_angle;
	uint8_t		mode_driving;
	uint8_t		mode_auto;
	uint8_t		mode_high_beam;
	uint8_t		mode_rain_road;
	uint8_t		mode_corner_light;
	uint8_t		mode_fog_light;
} esp32_info_t;

extern sensor_controller_t sensor_info;
extern esp32_info_t esp32_info;

#endif /* SRC_AP_AP_DEF_H_ */
