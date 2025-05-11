/*
 * ap.c
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */


#include "ap.h"



//uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  GPIO_PinState button_state = GPIO_PIN_SET;
  sensor_controller_t sensor_info;
void ap_init(void)
{
  //can_init(0x7f3, 0x106); // 필터 마스크, 필터 id를 인자로 입력

  //uartOpen(_DEF_UART1, 115200);
  scheduler_init();
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
	  app_scheduling();

//  	if (millis() - pre_time >= 10000)
//  	{
//    	temp = DHT_GetData();
//      //uartPrintf(_DEF_UART2, "Rx : %d\n", temp);
//
//  	}
    if (button_get_state(_DEF_BUTTON1) == false)
    {
      pre_time = millis();
      led_toggle(_DEF_LED1);
      uint16_t adc_data[3];
      adc_data[0] = adc_read(_DEF_ADC1);
      adc_data[1] = adc_read(_DEF_ADC2);
      adc_data[2] = adc_read(_DEF_ADC3);
      //uartPrintf(_DEF_UART2, "Rx : %d\n", adc_data);
    }

    //send_message(0x102, &data[0]); // can 메시지 전송
    //delay(1000); // 1초 딜레이

    cliMain();
	}
}

void app_scheduling(void)
{
    if (st_scheduling_info.u8nu_scheduling_1ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_1ms_flag = 0u;
        app_task_1ms();
    }

    if (st_scheduling_info.u8nu_scheduling_5ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_5ms_flag = 0u;
        app_task_5ms();
    }

    if (st_scheduling_info.u8nu_scheduling_10ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_10ms_flag = 0u;
        app_task_10ms();
    }

    if (st_scheduling_info.u8nu_scheduling_20ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_20ms_flag = 0u;
        app_task_20ms();
    }
}

void app_task_1ms(void)
{
}

void app_task_5ms(void)
{
	/*
	count++
	if(count < 4)
	{
		set sensor(count)
		sensor[count ] = get sensor
		if(sensor[3] >0)
		{
			set mode
			compare mode
		}
	}
	*/
}

void app_task_10ms(void)
{
}

void app_task_20ms(void)
{
	/*
	can trans
	count = 0;
	*/
}
