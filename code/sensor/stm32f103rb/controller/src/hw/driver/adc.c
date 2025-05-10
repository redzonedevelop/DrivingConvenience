/*
 * adc.c
 *
 *  Created on: May 10, 2025
 *      Author: jeff1
 */


#include "adc.h"

ADC_HandleTypeDef hadc1;

void adcInit(void)
{

  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
    __HAL_RCC_ADC1_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4);

  }
}


uint16_t HW_AdcReadChannel( uint32_t Channel )
{
  ADC_ChannelConfTypeDef adcConf = {0};
  uint16_t adcData = 0;

  adcConf.Channel = Channel;
  adcConf.Rank = ADC_REGULAR_RANK_1;
  adcConf.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;  // 또는 71.5, 안정성 목적

  if (HAL_ADC_ConfigChannel(&hadc1, &adcConf) != HAL_OK)
  {
    Error_Handler();  // 오류 발생 시 처리
  }

  HAL_ADC_Start(&hadc1);

  if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
  {
    adcData = HAL_ADC_GetValue(&hadc1);
  }

  HAL_ADC_Stop(&hadc1);

  return adcData;
}

