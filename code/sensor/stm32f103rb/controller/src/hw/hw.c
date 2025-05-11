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

  can_open();
  uartInit();
  cliInit();
  adc_init();
  led_init();

  button_init();
  dht11Init();

}
