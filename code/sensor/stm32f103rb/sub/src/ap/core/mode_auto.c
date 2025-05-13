/*
 * mode_auto.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_auto.h"
#include "sensor.h"

int auto_count;

void mode_auto_init()
{
	sensor_info.mode[STM_SUBORDINATE].mode_auto = AUTO_MODE_OFF;
	auto_count = 0;
}

void set_auto_mode()
{
	if (!sensor_info.error_flag.brightness_error)
	{
		if (get_sensor_brightness() > 2000)
		{
			 sensor_info.mode[STM_SUBORDINATE].mode_auto = AUTO_MODE_OFF;
		}
		else
		{
			 sensor_info.mode[STM_SUBORDINATE].mode_auto = AUTO_MODE_ON;
		}
	}
	return;
}

uint8_t get_auto_mode(int board)
{
	 return sensor_info.mode[board].mode_auto;
}


