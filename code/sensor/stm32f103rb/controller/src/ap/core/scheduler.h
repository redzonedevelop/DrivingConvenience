/*
 * scheduler.h
 *
 *  Created on: May 11, 2025
 *      Author: jeff1
 */

#ifndef SRC_COMMON_HW_INCLUDE_SCHEDULER_H_
#define SRC_COMMON_HW_INCLUDE_SCHEDULER_H_

#include "hw_def.h"

#ifdef _USE_HW_SCHEDULER

typedef struct
{
    uint8_t u8nu_scheduling_5ms_flag;
    uint8_t u8nu_scheduling_15ms_flag;
    uint8_t u8nu_scheduling_20ms_flag;
}scheduling_flag_t;

//typedef struct
//{
//    uint32_t u32nu_cnt_1ms;
//    uint32_t u32nu_cnt_5ms;
//    uint32_t u32nu_cnt_10ms;
//    uint32_t u32nu_cnt_20ms;
//}test_cnt_t;

extern scheduling_flag_t st_scheduling_info;
//extern test_cnt_t count_t;

void scheduler_init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void scheduler_update_flags(void);

#endif

#endif /* SRC_COMMON_HW_INCLUDE_SCHEDULER_H_ */
