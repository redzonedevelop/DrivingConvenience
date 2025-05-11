/*
 * mode_corner_light.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_corner_light.h"
#include "sensor.h"

int corner_threshold_left, corner_threshold_right;

void mode_corner_light_init()
{
	sensor_info.mode[STM_TRANS].mode_corner_light = CORNER_LIGHT_MODE_OFF;
	corner_threshold_left = 1000; // 임시 조향 기준값
	corner_threshold_right = 3000;
}

void set_corner_light_beam()
{
	int steering_angle = get_steering_angle();
	if (steering_angle < corner_threshold_left)
	{ // 좌회전
		sensor_info.mode[STM_TRANS].mode_corner_light = CORNER_LIGHT_MODE_LEFT;
	}
	else if (steering_angle > corner_threshold_right)
	{ // 우회전
		sensor_info.mode[STM_TRANS].mode_corner_light = CORNER_LIGHT_MODE_RIGHT;
	}
	else
	{ // 직진
		sensor_info.mode[STM_TRANS].mode_corner_light = CORNER_LIGHT_MODE_OFF;
	}
}
