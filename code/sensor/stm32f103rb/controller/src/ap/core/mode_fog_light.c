/*
 * mode_fog_light.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_fog_light.h"
#include "sensor.h"

int fog_light_count;

void mode_fog_light_init()
{
   sensor_info.mode[STM_TRANS].mode_fog_light = FOG_LIGHT_MODE_OFF;
   fog_light_count = 0;
}

void set_mode_fog_light()
{
	if(esp32_receive.humidity){
			sensor_info.mode[STM_TRANS].mode_fog_light = FOG_LIGHT_MODE_ON;
	}
	else{
			sensor_info.mode[STM_TRANS].mode_fog_light = FOG_LIGHT_MODE_OFF;
	}
	esp32_info.mode_fog_light = sensor_info.mode[STM_TRANS].mode_fog_light;
}

uint8_t get_mode_fog_light(int board)
{
   return sensor_info.mode[board].mode_fog_light;
}
