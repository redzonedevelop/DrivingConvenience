/*
 * mode_auto.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_AUTO_H_
#define SRC_AP_CORE_MODE_AUTO_H_

#include "ap_def.h"

typedef enum
{
	AUTO_MODE_ERROR	= 0b000, // 0
	AUTO_MODE_OFF	= 0b100,	 // 4
	AUTO_MODE_ON	= 0b100	 // 5
} auto_mode_t;

void mode_auto_init();
void set_auto_mode();
uint8_t get_auto_mode(int board);
void compare_auto_mode();

#endif /* SRC_AP_CORE_MODE_AUTO_H_ */
