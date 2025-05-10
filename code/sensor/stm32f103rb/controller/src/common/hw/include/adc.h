/*
 * adc.h
 *
 *  Created on: May 10, 2025
 *      Author: jeff1
 */

#ifndef SRC_COMMON_HW_INCLUDE_ADC_H_
#define SRC_COMMON_HW_INCLUDE_ADC_H_

#include "hw_def.h"

#ifdef _USE_HW_ADC

void adcInit(void);
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle);
uint16_t HW_AdcReadChannel( uint32_t Channel );
void set_sensor_photo_brightness( void );
void set_sensor_photo_darkness( void );

#endif

#endif /* SRC_COMMON_HW_INCLUDE_ADC_H_ */
