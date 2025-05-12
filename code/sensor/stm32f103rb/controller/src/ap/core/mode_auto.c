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
	sensor_info.mode[STM_TRANS].mode_auto = AUTO_MODE_OFF;
	auto_count = 0;
}

void set_auto_mode()
{
	if (!sensor_info.error_flag.brightness_error)
	{
		if (get_sensor_brightness() > 2000)
		{
			 sensor_info.mode[STM_CONTROLLER].mode_auto = AUTO_MODE_ON;
		}
		else
		{
			 sensor_info.mode[STM_CONTROLLER].mode_auto = AUTO_MODE_OFF;
		}
	}
}

uint8_t get_auto_mode(int board)
{
	 return sensor_info.mode[board].mode_auto;
}

void compare_auto_mode()
{
	if (!sensor_info.error_flag.brightness_error)
	{
		if (get_auto_mode(STM_CONTROLLER) == get_auto_mode(STM_SUBORDINATE))
		{
			sensor_info.mode[STM_TRANS].mode_auto = get_auto_mode(STM_CONTROLLER);
			if (auto_count > 0)
				auto_count--;
		}
		else
		{
			auto_count++;
			if (auto_count > 1000)
			{
				sensor_info.error_flag.brightness_error = true;
				sensor_info.mode[STM_TRANS].mode_auto = AUTO_MODE_ERROR;
			}
		}
	}
	else
	{
		 sensor_info.mode[STM_TRANS].mode_auto = AUTO_MODE_ERROR;
	}
	esp32_info.mode_auto = sensor_info.mode[STM_TRANS].mode_auto;
}
