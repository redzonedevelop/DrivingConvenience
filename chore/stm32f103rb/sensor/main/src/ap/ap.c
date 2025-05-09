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

}

void ap_main(void)
{
	uint32_t pre_time;
	uint8_t rx_buf[128];
	uint32_t rx_len;

	pre_time = millis();
	while(1)
	{
		if (millis() - pre_time >= 200)
		{
			pre_time = millis();
			led_toggle(_DEF_LED1);
		}

		rx_len = uartAvailable(_DEF_UART3);
		if(rx_len > 128)
		{
			rx_len = 128;
		}
		if(rx_len >0)
		{
			for (int i=0; i<rx_len; i++)
			{
				rx_buf[i] = uartRead(_DEF_UART3);
			}
			uartWrite(_DEF_UART2, rx_buf, rx_len);
			uartWrite(_DEF_UART3, "success\n\r", 9);
		}
	}
}
