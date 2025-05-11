/*
 * mode_seat.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_SEAT_H_
#define SRC_AP_CORE_MODE_SEAT_H_

#include "ap_def.h"

typedef enum
{
   SEAT_MODE_OFF     = 0b100, // 4
   SEAT_MODE_LEFT    = 0b101, // 5
   SEAT_MODE_RIGHT   = 0b110, // 6
   SEAT_MODE_BOTH    = 0b111  // 7
} seat_mode_t;

void mode_seat_init();
void set_seat_beam();

#endif /* SRC_AP_CORE_MODE_SEAT_H_ */
