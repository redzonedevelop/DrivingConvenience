/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan;

/* USER CODE BEGIN Private defines */
extern CAN_FilterTypeDef canFilter1;
extern CAN_RxHeaderTypeDef canRxHeader;
extern CAN_TxHeaderTypeDef canTxHeader;
extern uint8_t can1Rx0Data[8];
extern uint32_t TxMailBox;
extern uint8_t can1Tx0Data[8];
/* USER CODE END Private defines */

void MX_CAN_Init(void);
void filter_init(uint32_t filter_mask, uint32_t filter_id);
void send_message(uint32_t id, uint8_t* data);
void can_init(uint32_t filter_mask, uint32_t filter_id);
void print_message(void);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

