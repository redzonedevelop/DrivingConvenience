/*
 * scheduler.c
 *
 *  Created on: May 11, 2025
 *      Author: jeff1
 */


#include "scheduler.h"


TIM_HandleTypeDef htim2;  // 타이머 핸들 전역 정의
float us;
static uint32_t u32nu_counter_1ms = 0;

scheduling_flag_t st_scheduling_info;
//test_cnt_t st_test_cnt;

void scheduler_init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = (SystemCoreClock / 1000000) - 1; // 1MHz → 1µs tick
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000 - 1; // 1ms 주기
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(&htim2);
    HAL_TIM_Base_Start_IT(&htim2);

    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
    	scheduler_update_flags();  // 100µs마다 호출됨
    }
}

void scheduler_update_flags(void)
{
	u32nu_counter_1ms++;
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	st_scheduling_info.u8nu_scheduling_1ms_flag = 1;

    if (u32nu_counter_1ms % 5 == 0){
    	st_scheduling_info.u8nu_scheduling_5ms_flag = 1;
    }


    if (u32nu_counter_1ms % 10 == 0){
    	st_scheduling_info.u8nu_scheduling_10ms_flag = 1;
    }


    if (u32nu_counter_1ms % 20 == 0){
    	st_scheduling_info.u8nu_scheduling_20ms_flag = 1;
    }

	if (u32nu_counter_1ms >= 100000){
		u32nu_counter_1ms = 0;
	}

}


//void app_task_100us(void)
//{
//
//	st_test_cnt.u32nu_cnt_100us++;
//}
//
//void app_task_200us(void)
//{
//	st_test_cnt.u32nu_cnt_200us++;
//}
//
//void app_task_300us(void)
//{
//	st_test_cnt.u32nu_cnt_300us++;
//
//}
//
//void app_task_500us(void)
//{
//	st_test_cnt.u32nu_cnt_500us++;
//}
//void app_task_1000us(void)
//{
//	st_test_cnt.u32nu_cnt_1000us++;
//
//}

//void app_scheduling(void)
//{
//    if (st_scheduling_info.u8nu_scheduling_100us_flag == 1u)
//    {
//        st_scheduling_info.u8nu_scheduling_100us_flag = 0u;
//        app_task_100us();
//    }
//
//    if (st_scheduling_info.u8nu_scheduling_200us_flag == 1u)
//    {
//        st_scheduling_info.u8nu_scheduling_200us_flag = 0u;
//        app_task_200us();
//    }
//
//    if (st_scheduling_info.u8nu_scheduling_300us_flag == 1u)
//    {
//        st_scheduling_info.u8nu_scheduling_300us_flag = 0u;
//        app_task_300us();
//    }
//
//    if (st_scheduling_info.u8nu_scheduling_500us_flag == 1u)
//    {
//        st_scheduling_info.u8nu_scheduling_500us_flag = 0u;
//        app_task_500us();
//    }
//
//    if (st_scheduling_info.u8nu_scheduling_1000us_flag == 1u)
//    {
//        st_scheduling_info.u8nu_scheduling_1000us_flag = 0u;
//        app_task_1000us();
//    }
//}
