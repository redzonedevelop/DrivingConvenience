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

#define  DHT11_MAX_CH     HW_DHT11_MAX_CH

#define DHTLIB_OK               0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2

typedef struct
{
	uint8_t Temperature;
	uint8_t Humidity;
}DHT_DataTypedef;


uint8_t DHT_GetData (void);
void dht11Init(void);
void dwtInit(void);

#endif

#endif /* SRC_COMMON_HW_INCLUDE_DHT11_H_ */
