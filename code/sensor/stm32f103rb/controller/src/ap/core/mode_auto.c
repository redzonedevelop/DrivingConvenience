/*
 * mode_auto.c
 *
 * 낮인지 저녁인지 구별하는 조도센서로 판별
 *
 * 낮이면 (하향등 off) 저녁이면  (하향등 on)
 *
 * mode_auto_init : auto 모드 초기값 off 설정, error_count 초기화
 * set_auto_mode : controller의 조도센서를 통해서 auto 모드 설정
 * get_auto_mode : controller 및 subordinate의 auto 모드 get
 * compare_auto_mode : controller 및 subordinate의 auto 모드를 비교하여 최종 모드값 설정
 *  Created on: May 10, 2025
 *      Author: USER
 */

#include "mode_auto.h"

#define STM_TRANS		0
#define STM_CONTROLELR	1
#define STM_SUBORDINATE	2

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
		if (sensor_info.sensor_value.brightness)
		{
			// sensor_info.mode[STM_CONTROLELR].mode_.mode_value = RAINmode_MODE_ON;
		}
		else
		{
			// sensor_info.mode[STM_CONTROLELR].mode_rain_mode.mode_value = RAINmode_MODE_OFF;
		}
	}
}

uint8_t get_auto_mode(int board)
{
	// return sensor_info.mode[board].mode_rain_mode.mode_value;
}

void compare_auto_mode()
{
	if (!sensor_info.error_flag.brightness_error)
	{
		if (get_auto_mode(STM_CONTROLELR) == get_auto_mode(STM_SUBORDINATE))
		{
			// sensor_info.mode[STM_TRANS].mode_rain_mode.mode_value = get_auto_mode(STM_CONTROLELR);
			if (auto_count > 0)
			{
				auto_count--;
			}
		}
		else
		{
			auto_count++;
			if (auto_count > 10)
			{
				sensor_info.error_flag.brightness_error = true;
				// sensor_info.mode[STM_TRANS].mode_rain_mode.mode_value = AUTO_MODE_ERROR;
			}
		}
	}
	else
	{
		// sensor_info.mode[STM_TRANS].mode_rain_mode.mode_value = AUTO_MODE_ERROR;
	}
}
