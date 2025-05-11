/*
 * ap.c
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */


#include "ap.h"



//uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  GPIO_PinState button_state = GPIO_PIN_SET;


void ap_init(void)
{
  //can_init(0x7f3, 0x106); // 필터 마스크, 필터 id를 인자로 입력

  //uartOpen(_DEF_UART1, 115200);

  uartOpen(_DEF_UART2, 115200);
  cliOpen(_DEF_UART2, 115200);
}

void ap_main(void)
{
  uint32_t pre_time;
  uint8_t temp, temp_test;
  pre_time = millis();
  while(1)
  {

  	if (millis() - pre_time >= 10000)
  	{
    	temp = DHT_GetData();
      //uartPrintf(_DEF_UART2, "Rx : %d\n", temp);

  	}
    /*if (button_get_pressed(_DEF_BUTTON1) == true)
    {
      pre_time = millis();
      led_toggle(_DEF_LED1);
      uint16_t adc_data[3];
      adc_data[0] = adc_read(_DEF_ADC1);
      adc_data[1] = adc_read(_DEF_ADC2);
      adc_data[2] = adc_read(_DEF_ADC3);
      //uartPrintf(_DEF_UART2, "Rx : %d\n", adc_data);
    }*/

    //send_message(0x102, &data[0]); // can 메시지 전송
    //delay(1000); // 1초 딜레이

    cliMain();
	}
}
