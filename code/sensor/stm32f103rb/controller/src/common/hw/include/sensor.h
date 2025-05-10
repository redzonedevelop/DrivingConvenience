/*
 * sensor.h
 *
 *  Created on: May 10, 2025
 *      Author: jeff1
 */

#ifndef SRC_COMMON_HW_INCLUDE_SENSOR_H_
#define SRC_COMMON_HW_INCLUDE_SENSOR_H_

#include "hw_def.h"

#ifdef _USE_HW_SENSOR

typedef struct
{
   uint16_t speed;
   uint16_t steering_angle;
   uint16_t brightness;
   uint16_t darkness;
   uint16_t humidity;
   bool    rain;
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
    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_driving;

    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_high_beam;

    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_rain_road;

    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_corner_light;

    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_fog_light;

    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_seat;
} mode_t;

typedef struct
{
   sensor_value_t sensor_value;
   error_t  error_flag;
   mode_t    mode[3];
} sensor_controller_t;

void set_sensor_photo_brightness( void );
void set_sensor_photo_darkness( void );
void set_sensor_humidity( void );

extern sensor_controller_t sensor_info;

#endif

#endif /* SRC_COMMON_HW_INCLUDE_SENSOR_H_ */
