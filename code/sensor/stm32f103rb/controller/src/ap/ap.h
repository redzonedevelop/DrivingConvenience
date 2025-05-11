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

void ap_init(void);
void ap_main(void);

void app_scheduling(void);
void app_task_1ms(void);
void app_task_5ms(void);
void app_task_10ms(void);
void app_task_20ms(void);

#endif /* SRC_AP_AP_H_ */
