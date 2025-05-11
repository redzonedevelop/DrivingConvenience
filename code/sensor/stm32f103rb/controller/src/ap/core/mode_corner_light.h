/*
 * mode_corner_light.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_CORNER_LIGHT_H_
#define SRC_AP_CORE_MODE_CORNER_LIGHT_H_

#include "ap_def.h"

typedef enum
{
	CORNER_LIGHT_MODE_OFF	= 0b100,	// 4
	CORNER_LIGHT_MODE_LEFT	= 0b101, // 5
	CORNER_LIGHT_MODE_RIGHT	= 0b110 // 6
} corner_light_mode_t;

void mode_corner_light_init();
void set_corner_light_beam();

#endif /* SRC_AP_CORE_MODE_CORNER_LIGHT_H_ */
