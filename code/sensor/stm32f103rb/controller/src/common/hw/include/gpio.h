/*
 * gpio.h
 *
 *  Created on: May 11, 2025
 *      Author: hong
 */

#ifndef SRC_COMMON_HW_INCLUDE_GPIO_H_
#define SRC_COMMON_HW_INCLUDE_GPIO_H_


#include "hw_def.h"

#ifdef _USE_HW_GPIO

#define GPIO_MAX_CH      HW_GPIO_MAX_CH


typedef struct
{
  GPIO_TypeDef *port;
  uint32_t      pin;
  uint8_t       mode;
  GPIO_PinState on_state;
  GPIO_PinState off_state;
  bool          init_value;
} gpio_tbl_t;


bool gpio_init(void);
bool gpio_pin_mode(uint8_t ch, uint8_t mode);
void gpio_pin_write(uint8_t ch, bool value);
bool gpio_pin_read(uint8_t ch);
void gpio_pin_toggle(uint8_t ch);


#endif

#endif /* SRC_COMMON_HW_INCLUDE_GPIO_H_ */
