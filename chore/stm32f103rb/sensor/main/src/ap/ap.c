/*
 * ap.c
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */


#include "ap.h"





void ap_init(void)
{
  uartOpen(_DEF_UART2, 115200);

  uartOpen(_DEF_UART3, 115200);
  cliOpen(_DEF_UART3, 115200);
}

void ap_main(void)
{
  uint32_t pre_time;


  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      led_toggle(_DEF_LED1);
    }

    if (uartAvailable(_DEF_UART3) > 0)
    {
      uint8_t rx_data;
      rx_data = uartRead(_DEF_UART3);

      //uartPrintf(_DEF_UART3, "Rx : 0x%X\n", rx_data);
    }

    cliMain();
	}
}
