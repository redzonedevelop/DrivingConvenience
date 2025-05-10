/*
 * dht11.h
 *
 *  Created on: May 10, 2025
 *      Author: jeff1
 */

#ifndef SRC_COMMON_HW_INCLUDE_DHT11_H_
#define SRC_COMMON_HW_INCLUDE_DHT11_H_

#include "hw_def.h"

#ifdef _USE_HW_DHT11

#define DHTLIB_OK               0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2

typedef struct
{
	float Temperature;
	float Humidity;
}DHT_DataTypedef;


int DHT_GetData (DHT_DataTypedef *DHT_Data);
void dht11Init(void);
void dwtInit(void);

#endif

#endif /* SRC_COMMON_HW_INCLUDE_DHT11_H_ */
