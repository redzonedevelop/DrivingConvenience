/*
 * darkness.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "sensor.h"
#include "darkness.h"
#include "cli.h"

#define DARKNESS_PORT GPIOB
#define DARKNESS_PIN GPIO_PIN_15

bool darkness_init(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin : Button_Pin */
	GPIO_InitStruct.Pin = DARKNESS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DARKNESS_PORT, &GPIO_InitStruct);

	sensor_info.sensor_value.darkness = 0;

	return true;
}

void set_sensor_darkness(){
	sensor_info.sensor_value.darkness = !sensor_info.sensor_value.darkness;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == DARKNESS_PIN)
    {
        set_sensor_darkness();
    }
}

bool get_sensor_darkness(){
	return sensor_info.sensor_value.darkness;
}

void set_mode_darkness(){

}

void get_mode_darkness(){

}

void compare_mode_darkness(){

}
