/*
 * ap.h
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */

#ifndef SRC_AP_AP_H_
#define SRC_AP_AP_H_


#include "hw.h"
#include "ap_def.h"
#include "scheduler.h"
#include "mode_auto.h"
#include "mode_fog_light.h"
#include "mode_high_beam.h"
#include "mode_rain_road.h"
#include "sensor.h"

void ap_init(void);
void ap_main(void);

void app_scheduling(void);

void app_task_5ms(void);
void app_task_15ms(void);
void app_task_20ms(void);

#endif /* SRC_AP_AP_H_ */
