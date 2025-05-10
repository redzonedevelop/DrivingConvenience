/*
 * uart.h
 *
 *  Created on: Feb 16, 2025
 *      Author: zvxc3
 */

#ifndef SRC_COMMON_HW_INCLUDE_UART_H_
#define SRC_COMMON_HW_INCLUDE_UART_H_


#include "hw_def.h"


#ifdef _USE_HW_UART

#define UART_MAX_CH         HW_UART_MAX_CH



bool      uart_init(void);
bool      uart_open(uint8_t ch, uint32_t baud);
uint32_t  uart_available(uint8_t ch);
uint8_t   uart_read(uint8_t ch);
uint32_t  uart_write(uint8_t ch, uint8_t *p_data, uint32_t length);
uint32_t  uart_printf(uint8_t ch, char *fmt, ...);
uint32_t uart_get_baud(uint8_t ch);


#endif

#endif /* SRC_COMMON_HW_INCLUDE_UART_H_ */
