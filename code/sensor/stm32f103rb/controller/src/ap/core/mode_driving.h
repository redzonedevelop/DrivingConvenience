/*
 * mode_driving.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_DRIVING_H_
#define SRC_AP_CORE_MODE_DRIVING_H_

#include "ap_def.h"

typedef enum
{
   DRIVING_MODE_URBAN   = 0b100, // 4
   DRIVING_MODE_COUNTRY = 0b101, // 5
   DRIVING_MODE_HIGHWAY = 0b110  // 6
} driving_mode_t;

void mode_driving_init();
void set_mode_driving();
void set_threshold(uint8_t mode_driving);

#endif /* SRC_AP_CORE_MODE_DRIVING_H_ */
