/*
 * qbuffer.h
 *
 *  Created on: Feb 16, 2025
 *      Author: zvxc3
 */

#ifndef SRC_HW_DRIVER_QBUFFER_H_
#define SRC_HW_DRIVER_QBUFFER_H_


#ifdef __cplusplus // c++ project에서도 헤더를 호출할 수 있도록
extern "C" {
#endif


#include "def.h" // 하드웨어와 상관이 없이 공통으로 사용하기 때문에 hw_def 필요 없음


typedef struct
{
  uint32_t in;
  uint32_t out;
  uint32_t len;

  uint8_t *p_buf; // buffer의 size는 사용하는 쪽에서 선택할 수 있도록
}qbuffer_t;


void qbufferInit(void);


bool        qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length);
bool        qbufferWrite(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
bool        qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
uint32_t    qbufferAvailable(qbuffer_t *p_node); // 현재 buffer에 있는 개수를 넘긴다.
void        qbufferFlush(qbuffer_t *p_node); // buffer 비우기 in과 out이 동일한 경우 비운다.

#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_DRIVER_QBUFFER_H_ */
