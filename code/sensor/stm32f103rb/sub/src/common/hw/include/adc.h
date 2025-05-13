/*
 * adc.h
 *
 *  Created on: May 10, 2025
 *      Author: HONG
 */

#ifndef SRC_COMMON_HW_INCLUDE_ADC_H_
#define SRC_COMMON_HW_INCLUDE_ADC_H_


#include "hw_def.h"

#ifdef _USE_HW_ADC


#define ADC_MAX_CH    HW_ADC_MAX_CH


typedef struct
{
  uint32_t channel;
  uint32_t rank;
  uint32_t sampling_time;
} adc_tbl_t;

void     adc_init(void);
uint16_t adc_read(uint8_t ch);

#endif


#endif /* SRC_COMMON_HW_INCLUDE_ADC_H_ */
