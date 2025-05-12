/*
 * sensor_rain.c
 *
 *  Created on: May 11, 2025
 *      Author: USER
 */

#include "sensor.h"

void set_speed(int count){
	sensor_info.car_value[count].speed = adc_read(_DEF_ADC1);

	if (count == 2)
	{
		int sum = sensor_info.car_value[0].speed + sensor_info.car_value[1].speed + sensor_info.car_value[2].speed;
		int value = (int)(sum/3/25);
		sensor_info.car_value[3].speed = value;
		esp32_info.speed = value;
	}
}

int get_speed()
{
	return sensor_info.car_value[3].speed;
}

void set_steering_angle(int count)
{
	sensor_info.car_value[count].steering_angle = adc_read(_DEF_ADC3);

	if (count == 2)
	{
		int sum = sensor_info.car_value[0].steering_angle + sensor_info.car_value[1].steering_angle + sensor_info.car_value[2].steering_angle;
		int value = (int)(sum/3);
		sensor_info.car_value[3].steering_angle = value;
		esp32_info.steering_angle = value;
	}
}

int get_steering_angle(){
	return sensor_info.car_value[3].steering_angle;
}

void set_sensor_brightness(int count)
{
	if (!sensor_info.error_flag.brightness_error)
		{
			sensor_info.sensor_value[count].brightness = adc_read(_DEF_ADC2);

			if (count == 2)
			{
				int sum = sensor_info.sensor_value[0].brightness + sensor_info.sensor_value[1].brightness + sensor_info.sensor_value[2].brightness;
				int value = (int)(sum/3);
				sensor_info.sensor_value[3].brightness = value;
			}
		}
}

int get_sensor_brightness(){
	return sensor_info.sensor_value[3].brightness;
}

void set_sensor_darkness(int count)
{
	if (!sensor_info.error_flag.darkness_error)
	{
		sensor_info.sensor_value[count].darkness = button_get_state(_DEF_BUTTON1);

		if (count == 2)
		{
			int sum = sensor_info.sensor_value[0].darkness + sensor_info.sensor_value[1].darkness + sensor_info.sensor_value[2].darkness;
			bool value = (sum >= 2) ? 1 : 0;
			sensor_info.sensor_value[3].darkness = value;
		}
	}
}

bool get_sensor_darkness()
{
	return sensor_info.sensor_value[3].darkness;
}

void set_esp32(){

	esp32_receive.humidity = uartRead(_DEF_UART1);
	esp32_receive.rain = uartRead(_DEF_UART1);
}

void set_sensor_rain(int count){
	if (!sensor_info.error_flag.rain_error)
	{
		sensor_info.sensor_value[count].rain = gpio_pin_read(_DEF_GPIO2);

		if (count == 2)
		{
			int sum = sensor_info.sensor_value[0].rain + sensor_info.sensor_value[1].rain + sensor_info.sensor_value[2].rain;
			bool value = (sum >= 2) ? 1 : 0;
			sensor_info.sensor_value[3].rain = value;
		}
	}
}

bool get_sensor_rain()
{
   return sensor_info.sensor_value[3].rain;
}
