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
  esp32_receive_t esp32_receive;
  esp32_info_t esp32_info;
  uint8_t count = 0;

void ap_init(void)
{
  can_init(0x7FF, 0x112); // 필터 마스크, 필터 id를 인자로 입력

  uartOpen(_DEF_UART1, 115200);
  mode_auto_init();
  mode_corner_light_init();
  mode_driving_init();
  mode_fog_light_init();
  mode_high_beam_init();
  mode_rain_road_init();
  mode_seat_init();
  scheduler_init();
//  uartOpen(_DEF_UART2, 115200);
//  cliOpen(_DEF_UART2, 115200);
  sensor_info.mode[0].mode_auto = AUTO_MODE_ON;


}

void ap_main(void)
{
//  uint32_t pre_time;
//  uint8_t temp;
//  pre_time = millis();
  while(1)
  {
	  app_scheduling();
//	  send_message(0x111, &sensor_info.mode[0]);
//	  delay(200);

//  	if (millis() - pre_time >= 10000)
//  	{
//    	temp = DHT_GetData();
//      //uartPrintf(_DEF_UART2, "Rx : %d\n", temp);
//
//  	}
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
//    delay(1000); // 1초 딜레이

//    cliMain();
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
		set_speed(count);
		set_steering_angle(count);
		set_sensor_brightness(count);
		set_sensor_darkness(count);
		set_sensor_rain(count);
	}
	count++;
	if (count == 3){
		set_esp32();
		count = 0;
	}
}

void app_task_15ms(void)
{
	set_auto_mode();
	set_corner_light_beam();
	set_mode_driving();
	set_mode_fog_light();
//	set_mode_high_beam();
	set_mode_rain_road();
	set_seat_beam();
	//compare_auto_mode();
//	compare_mode_high_beam();
//	compare_mode_rain_road();
}

void app_task_20ms(void)
{
	send_message(0x111, (uint8_t*)&sensor_info.mode[0]);
	uartWrite(_DEF_UART1, (uint8_t*)&esp32_info, 10);

}
