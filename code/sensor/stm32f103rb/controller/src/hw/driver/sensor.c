/*
 * sensor.c
 *
 *  Created on: May 10, 2025
 *      Author: jeff1
 */

#include "sensor.h"
#include "dht11.h"
sensor_controller_t sensor_info;
DHT_DataTypedef DHT11_Data;

void set_sensor_photo_brightness( void )
{
	sensor_info.sensor_value.brightness =  HW_AdcReadChannel( ADC_CHANNEL_1 );
}

void set_sensor_photo_darkness( void )
{
	sensor_info.sensor_value.darkness =  HW_AdcReadChannel( ADC_CHANNEL_0 );
}

void set_sensor_humidity( void )
{
	int res = DHT_GetData(&DHT11_Data);
	if(res < 0)
	{
		switch(res)
		{
			case DHTLIB_ERROR_CHECKSUM:
//				Printf("DHT_GetData DHTLIB_ERROR_CHECKSUM\r\n");
				break;
			case DHTLIB_ERROR_TIMEOUT:
//				Printf("DHT_GetData DHTLIB_ERROR_TIMEOUT\r\n");
				break;
		}
	}
	else
	{
		sensor_info.sensor_value.humidity = DHT11_Data.Humidity;
	}
}

uint16_t get_sensor_photo_brightness( void )
{

	return 0;
}

