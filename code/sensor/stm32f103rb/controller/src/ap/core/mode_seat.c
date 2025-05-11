/*
 * mode_seat.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_seat.h"
#include "sensor.h"

#define STM_TRANS		0
#define STM_CONTROLELR	1
#define STM_SUBORDINATE	2

int seat_threshold_left, seat_threshold_right;

void mode_seat_init()
{
	sensor_info.mode[STM_TRANS].mode_corner_light.mode_value = SEAT_MODE_OFF;
	seat_threshold_left = 1000; // 임시 조향 기준값
	seat_threshold_right = 3000;
}

void set_seat_beam()
{
	int tmp = 2500;	 // 임시 조향값
	int speed = 120; // 임시 속도값

	if (speed > 100)
	{
		sensor_info.mode[STM_TRANS].mode_seat.mode_value = SEAT_MODE_BOTH;
	}
	else if (speed > 50)
	{
		if (tmp < seat_threshold_left)
		{ // 좌회전
			sensor_info.mode[STM_TRANS].mode_seat.mode_value = SEAT_MODE_LEFT;
		}
		else if (tmp > seat_threshold_right)
		{ // 우회전
			sensor_info.mode[STM_TRANS].mode_seat.mode_value = SEAT_MODE_RIGHT;
		}
		else
		{ // 직진
			sensor_info.mode[STM_TRANS].mode_seat.mode_value = SEAT_MODE_OFF;
		}
	}
}
