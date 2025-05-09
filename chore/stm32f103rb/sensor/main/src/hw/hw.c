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

	led_init();
  uartInit();

}
