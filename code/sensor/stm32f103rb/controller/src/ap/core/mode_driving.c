/*
 * mode_driving.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_driving.h"
#include "sensor.h"

int driving_threshold_min, driving_threshold_max;

void mode_driving_init()
{
	sensor_info.mode[STM_TRANS].mode_driving = DRIVING_MODE_URBAN;
	set_threshold(DRIVING_MODE_URBAN);
}

void set_mode_driving()
{
	int speed = get_speed();
	if (speed < driving_threshold_min)
	{ // 주행모드 내려가기
		sensor_info.mode[STM_TRANS].mode_driving--;
		set_threshold(sensor_info.mode[STM_TRANS].mode_driving);
	}
	else if (speed > driving_threshold_max)
	{ // 주행모드 올라가기
		sensor_info.mode[STM_TRANS].mode_driving++;
		set_threshold(sensor_info.mode[STM_TRANS].mode_driving);
	}
}

void set_threshold(uint8_t mode_driving)
{
	if (mode_driving == DRIVING_MODE_URBAN)
	{
		driving_threshold_min = 0;
		driving_threshold_max = 55;
	}
	else if (mode_driving == DRIVING_MODE_COUNTRY)
	{
		driving_threshold_min = 45;
		driving_threshold_max = 105;
	}
	else if (mode_driving == DRIVING_MODE_HIGHWAY)
	{
		driving_threshold_min = 95;
		driving_threshold_max = 200;
	}
}
