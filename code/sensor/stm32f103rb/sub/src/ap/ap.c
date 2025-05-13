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
  uint8_t count = 0;

void ap_init(void)
{
  can_init(0x000, 0x000); // 필터 마스크, 필터 id를 인자로 입력

  //uartOpen(_DEF_UART1, 115200);
  scheduler_init();
}

void ap_main(void)
{
  uint32_t pre_time;
  uint8_t temp;
  pre_time = millis();
  while(1)
  {
	  app_scheduling();
//	  send_message(0x111, &sensor_info.mode[2]);
//	  delay(2000);
	}
}

void app_scheduling(void)
{
    if (st_scheduling_info.u8nu_scheduling_5ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_5ms_flag = 0u;
        app_task_5ms();
    }

    if (st_scheduling_info.u8nu_scheduling_15ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_15ms_flag = 0u;
        app_task_15ms();
    }

    if (st_scheduling_info.u8nu_scheduling_20ms_flag == 1u)
    {
        st_scheduling_info.u8nu_scheduling_20ms_flag = 0u;
        app_task_20ms();
    }
}


void app_task_5ms(void)
{

	if(count < 3)
	{
		set_sensor_brightness(count);
		set_sensor_darkness(count);
		set_sensor_rain(count);
	}
	count++;
	if (count == 3){
		count = 0;
	}
}

void app_task_15ms(void)
{
	set_auto_mode();
	set_mode_fog_light();
	set_mode_high_beam();
	set_mode_rain_road();
}

void app_task_20ms(void)
{
	send_message(0x112, &sensor_info.mode[2]);
}
