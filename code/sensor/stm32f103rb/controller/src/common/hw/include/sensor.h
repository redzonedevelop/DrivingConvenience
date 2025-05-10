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

typedef enum {
   SPEED_MODE_URBAN = 0,
   SPEED_MODE_COUNTRY,
   SPEED_MODE_HIGHWAY,
} speed_mode_t;

typedef enum {
   HIGHBEAM_MODE_OFF = 0,
   HIGHBEAM_MODE_ON,
} highbeam_mode_t;

typedef enum {
   RAINROAD_MODE_OFF = 0,
   RAINROAD_MODE_ON,
} rain_road_mode_t;

typedef enum {
   CORNER_LIGHT_OFF = 0,
   CORNER_LIGHT_LEFT,
   CORNER_LIGHT_RIGHT,
} corner_light_mode_t;

typedef enum {
   SEAT_MODE_OFF = 0,
   SEAT_MODE_LEFT,
   SEAT_MODE_RIGHT,
   SEAT_MODE_HIGHWAY,
} seat_mode_t;


typedef struct
{
	uint16_t speed;
   uint16_t steering_angle;
   uint16_t brightness;
   uint16_t darkness;
   uint16_t humidity;
   bool    rain_flag;
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
    } mode_speed;

    struct {
        uint8_t mode_value : 3;
        uint8_t reserved   : 5;
    } mode_highbeam;

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
   mode_t    mode;
} sensor_controller_t;

void set_sensor_photo_brightness( void );
void set_sensor_photo_darkness( void );
void set_sensor_humidity( void );

#endif

#endif /* SRC_COMMON_HW_INCLUDE_SENSOR_H_ */
