/*
 * ap.c
 *
 *  Created on: May 5, 2025
 *      Author: USER
 */


#include "ap.h"


uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};


void ap_init(void)
{
  can_init(0x7f3, 0x106); // 필터 마스크, 필터 id를 인자로 입력
}

void ap_main(void)
{
  while(1)
  {
    send_message(0x102, &data[0]); // can 메시지 전송
    delay(1000); // 1초 딜레이
  }
}
