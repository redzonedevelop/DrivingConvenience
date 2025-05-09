/*
 * main.c
 *
 *  Created on: May 2, 2025
 *      Author: USER
 */


#include "main.h"





int main(void)
{
  hw_init();
  ap_init();

  ap_main();
  return 0;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) // can 메시지 수신 인터럽트
{
  if (hcan->Instance == CAN1)
    {
      HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &canRxHeader, can1Rx0Data);
      print_message(); // 메시지를 UART로 출력
    }

}
