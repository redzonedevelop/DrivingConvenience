/*
 * can.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef SRC_COMMON_HW_INCLUDE_CAN_H_
#define SRC_COMMON_HW_INCLUDE_CAN_H_


#include "hw_def.h"


#ifdef _USE_HW_CAN

#define CAN_MAX_CH     HW_CAN_MAX_CH

void can_open(void);
void filter_init(uint32_t filter_mask, uint32_t filter_id);
void send_message(uint32_t id, uint8_t* data);
void can_init(uint32_t filter_mask, uint32_t filter_id);
void print_message(void);


#endif /* __CAN_H__ */

#endif /* SRC_COMMON_HW_INCLUDE_CAN_H_ */
