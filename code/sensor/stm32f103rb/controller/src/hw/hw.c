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
  cliInit();
  led_init();
  uartInit();
  adcInit();
  dwtInit();
  dht11Init();
}
