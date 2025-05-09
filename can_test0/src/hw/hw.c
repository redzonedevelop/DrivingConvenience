/*
 * hw.c
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */


#include "hw.h"






void hw_init(void)
{
  bsp_init();
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_USART2_UART_Init();
}
