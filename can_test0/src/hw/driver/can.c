/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_FilterTypeDef canFilter1;
CAN_RxHeaderTypeDef canRxHeader;
CAN_TxHeaderTypeDef canTxHeader;
uint8_t can1Rx0Data[8];
uint32_t TxMailBox;
uint8_t can1Tx0Data[8];
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void filter_init(uint32_t filter_mask, uint32_t filter_id){
  canFilter1.FilterMaskIdHigh = filter_mask << 5; // 필터 마스크를 111 1111 0011 로 설정
  canFilter1.FilterIdHigh = filter_id << 5; // 필터 Id를 001 0000 0110 으로 설정
  canFilter1.FilterMaskIdLow = filter_mask << 5;
  canFilter1.FilterIdLow = filter_id << 5;
  canFilter1.FilterMode = CAN_FILTERMODE_IDMASK; // IDMASK 모드 사용
  canFilter1.FilterScale = CAN_FILTERSCALE_16BIT;
  canFilter1.FilterFIFOAssignment = CAN_FILTER_FIFO0; // 0번 버퍼 사용
  canFilter1.FilterBank = 0;
  canFilter1.FilterActivation = ENABLE;

  HAL_CAN_ConfigFilter(&hcan, &canFilter1); // 필터 적용
}

void send_message(uint32_t id, uint8_t* data){
  canTxHeader.StdId = id; // 송신 메시지 ID 설정 001 0000 0010
  canTxHeader.RTR = CAN_RTR_DATA; // Data frame 사용
  canTxHeader.IDE = CAN_ID_STD; // 11비트 ID 사용
  canTxHeader.DLC = 8; // 8Byte 데이터 크기 사용

  for(int i=0;i<8;i++) {
    can1Tx0Data[i] = data[i];
  }

  TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan); // 비어 있는 메일 박스 번호가 리턴된다.
  HAL_CAN_AddTxMessage(&hcan, &canTxHeader, &can1Tx0Data[0], &TxMailBox); // 해당 메일 박스에 송신할 메시지를 추가
}

void can_init(uint32_t filter_mask, uint32_t filter_id){
  filter_init(filter_mask, filter_id); // can 필터 생성
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); // 수신 인터럽트 ON
  HAL_CAN_Start(&hcan); // can 모듈 시작
}

void print_message(){
  // 메시지를 문자열로 변환
  char uartBuf[100];

  snprintf(uartBuf, sizeof(uartBuf),
  "CAN ID: 0x%03X | DATA: %02X %02X %02X %02X %02X %02X %02X %02X\r\n",
  canRxHeader.StdId,
  can1Rx0Data[0], can1Rx0Data[1], can1Rx0Data[2], can1Rx0Data[3],
  can1Rx0Data[4], can1Rx0Data[5], can1Rx0Data[6], can1Rx0Data[7]);

  // UART2로 송신 (USB-Serial 통해 PC로 전송됨)
  HAL_UART_Transmit(&huart2, (uint8_t*)uartBuf, strlen(uartBuf), HAL_MAX_DELAY);
}
/* USER CODE END 1 */
