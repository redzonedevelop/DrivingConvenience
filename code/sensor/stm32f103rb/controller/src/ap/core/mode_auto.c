/*
 * mode_auto.c
 *
 *  Created on: May 10, 2025
 *      Author: USER
 */

#include "mode_rain_road.h"
#include "sensor.h"

#define STM_TRANS		0
#define STM_CONTROLELR	1
#define STM_SUBORDINATE	2

int auto_count;

void mode_auto_init()
{
	// sensor_info.mode[STM_TRANS].mode_.mode_value = RAINROAD_MODE_OFF;
	auto_count = 0;
}

void set_auto_road()
{
	if (!sensor_info.error_flag.brightness_error)
	{
		if (sensor_info.sensor_value.brightness)
		{
			// sensor_info.mode[STM_CONTROLELR].mode_.mode_value = RAINROAD_MODE_ON;
		}
		else
		{
			// sensor_info.mode[STM_CONTROLELR].mode_rain_road.mode_value = RAINROAD_MODE_OFF;
		}
	}
}

uint8_t get_auto_road(int board)
{
	// return sensor_info.mode[board].mode_rain_road.mode_value;
}

void compare_auto_road()
{
	if (!sensor_info.error_flag.brightness_error)
	{
		if (get_auto_road(STM_CONTROLELR) == get_auto_road(STM_SUBORDINATE))
		{
			// sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = get_auto_road(STM_CONTROLELR);
			if (auto_count > 0)
				auto_count--;
		}
		else
		{
			auto_count++;
			if (auto_count > 7)
			{
				sensor_info.error_flag.brightness_error = true;
				// sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = AUTO_MODE_ERROR;
			}
		}
	}
	else
	{
		// sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = AUTO_MODE_ERROR;
	}
}
