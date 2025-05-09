/*
 * led.h
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */

#ifndef SRC_COMMON_HW_INCLUDE_LED_H_
#define SRC_COMMON_HW_INCLUDE_LED_H_


#include "hw_def.h"


#ifdef _USE_HW_LED

#define LED_MAX_CH     HW_LED_MAX_CH

bool led_init(void);
void led_on(uint8_t ch);
void led_off(uint8_t ch);
void led_toggle(uint8_t ch);

#endif


#endif /* SRC_COMMON_HW_INCLUDE_LED_H_ */
