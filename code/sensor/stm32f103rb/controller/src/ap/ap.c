/*
 * ap.c
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */


#include "ap.h"



uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};


void ap_init(void)
{
  //can_init(0x7f3, 0x106); // 필터 마스크, 필터 id를 인자로 입력

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
	  set_sensor_photo_brightness();
	  set_sensor_photo_darkness();
	  set_sensor_humidity();
	  set_sensor_rain();
//    if (millis()-pre_time >= 500)
//    {
//      pre_time = millis();
//      led_toggle(_DEF_LED1);
//    }
//
//    if (uartAvailable(_DEF_UART3) > 0)
//    {
//      uint8_t rx_data;
//      rx_data = uartRead(_DEF_UART3);
//
//      //uartPrintf(_DEF_UART3, "Rx : 0x%X\n", rx_data);
//    }
    //send_message(0x102, &data[0]); // can 메시지 전송
    delay(1000); // 1초 딜레이

//    cliMain();
	}
}
