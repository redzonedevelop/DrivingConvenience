/*
 * mode_rain_road.h
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#ifndef SRC_AP_CORE_MODE_RAIN_ROAD_H_
#define SRC_AP_CORE_MODE_RAIN_ROAD_H_

#include "ap_def.h"

typedef enum {
    RAINROAD_MODE_ERROR    = 0b000,  // 0
    RAINROAD_MODE_OFF      = 0b100,  // 4
    RAINROAD_MODE_ON       = 0b101   // 5
} rain_road_mode_t;

void mode_rain_road_init();
void set_mode_rain_road();
uint8_t get_mode_rain_road();
void compare_mode_rain_road();

#endif /* SRC_AP_CORE_MODE_RAIN_ROAD_H_ */
