/*
 * mode_fog_light.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_FOG_LIGHT_H_
#define SRC_AP_CORE_MODE_FOG_LIGHT_H_

#include "ap_def.h"

typedef enum
{
	FOG_LIGHT_MODE_ERROR	= 0b000,	// 0
	FOG_LIGHT_MODE_OFF		= 0b100,	// 4
	FOG_LIGHT_MODE_ON		= 0b101,	// 5
} fot_light_mode_t;

void mode_fog_light_init();
void set_mode_fog_light();
uint8_t get_mode_fog_light(int board);
void compare_mode_fog_light();

#endif /* SRC_AP_CORE_MODE_FOG_LIGHT_H_ */
