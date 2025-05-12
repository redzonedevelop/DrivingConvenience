/*
 * sensor_rain.c
 *
 *  Created on: May 11, 2025
 *      Author: USER
 */

#include "sensor.h"


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

void set_sensor_humidity(int count){
	// uart read
}

int get_sensor_humidity(){
	return sensor_info.sensor_value[3].humidity;
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
