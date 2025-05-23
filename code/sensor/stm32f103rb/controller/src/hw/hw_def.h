/*
 * hw_def.h
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"
//#include ""


#define _USE_HW_ADC
#define     HW_ADC_MAX_CH     3


#define _USE_HW_LED
#define     HW_LED_MAX_CH     1


#define _USE_HW_UART
#define     HW_UART_MAX_CH    2


#define _USE_HW_CAN
#define     HW_CAN_MAX_CH     1


#define _USE_HW_DHT11
#define     HW_DHT11_MAX_CH   1


#define _USE_HW_BUTTON
#define    HW_BUTTON_MAX_CH   1

#define _USE_HW_GPIO
#define    HW_GPIO_MAX_CH     2


#define _USE_HW_CLI
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    32

#define _USE_HW_SCHEDULER

#endif /* SRC_HW_HW_DEF_H_ */
