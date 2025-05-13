/*
 * mode_high_beam.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_HIGH_BEAM_H_
#define SRC_AP_CORE_MODE_HIGH_BEAM_H_

#include "ap_def.h"

typedef enum
{
	HIGH_BEAM_MODE_ERROR	= 0b000,	// 0
	HIGH_BEAM_MODE_OFF		= 0b100,	// 4
	HIGH_BEAM_MODE_ON		= 0b101		// 5
} high_beam_mode_t;

void mode_high_beam_init();
void set_mode_high_beam();
uint8_t get_mode_high_beam();
void compare_mode_high_beam();

#endif /* SRC_AP_CORE_MODE_HIGH_BEAM_H_ */
