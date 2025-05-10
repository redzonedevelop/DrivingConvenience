/*
 * rain.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */


#include "sensor.h"
#include "rain.h"
#include "cli.h"

#define RAIN_PORT GPIOA
#define RAIN_PIN GPIO_PIN_8

bool rain_init(){
	  /*Configure GPIO pin : Rain_sensor_Pin */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = RAIN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(RAIN_PORT, &GPIO_InitStruct);

	return true;
}

void set_sensor_rain(){
	sensor_info.sensor_value.rain_flag = HAL_GPIO_ReadPin(RAIN_PORT, RAIN_PIN);
}

void get_sensor_rain(){

}

void set_mode_rain(){

}

void get_mode_rain(){

}

void compare_mode_rain(){

}
