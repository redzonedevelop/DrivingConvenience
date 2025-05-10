/*
 * sensor_rain.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "sensor.h"
#include "sensor_rain.h"
#include "cli.h"

#define RAIN_PORT GPIOA
#define RAIN_PIN GPIO_PIN_8

void sensor_rain_init(){
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   GPIO_InitStruct.Pin = RAIN_PIN;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(RAIN_PORT, &GPIO_InitStruct);
}

void set_sensor_rain(){
   if (!sensor_info.error_flag.rain_error)
      sensor_info.sensor_value.rain = HAL_GPIO_ReadPin(RAIN_PORT, RAIN_PIN);
}

bool get_sensor_rain(){
   return sensor_info.sensor_value.rain;
}

