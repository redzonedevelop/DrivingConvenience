/*
 * hw.c
 *
 *  Created on: May 2, 2025
 *      Author: DAWIT
 */


#include "hw.h"






void hw_init(void)
{
  bsp_init();

  //can_open();
  cli_init();
  led_init();
  uart_init();
}
