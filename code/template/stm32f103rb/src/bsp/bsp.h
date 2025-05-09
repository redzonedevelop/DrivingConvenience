/*
 * bsp.h
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_


#include "def.h"


#include "stm32f1xx_hal.h"


void bsp_init(void);
void delay(uint32_t ms);
uint32_t millis(void);

void Error_Handler(void);

#endif /* SRC_BSP_BSP_H_ */
