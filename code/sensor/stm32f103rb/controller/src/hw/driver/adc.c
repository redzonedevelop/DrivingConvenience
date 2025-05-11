/*
 * adc.c
 *
 *  Created on: May 10, 2025
 *      Author: USER
 */


#include "adc.h"


ADC_HandleTypeDef hadc1;

uint16_t adc_data[ADC_MAX_CH];

adc_tbl_t adc_tbl[ADC_MAX_CH] =
    {
        {ADC_CHANNEL_0, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_71CYCLES_5},
        {ADC_CHANNEL_1, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_71CYCLES_5},
        {ADC_CHANNEL_4, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_71CYCLES_5},
    };


void adc_init(void)
{

  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

}

uint16_t adc_read(uint8_t ch)
{
	uint16_t ret = 0;

  if (ch >= ADC_MAX_CH)
  {
  	Error_Handler();
  }
  ADC_ChannelConfTypeDef sConfig = {0};

  sConfig.Channel = adc_tbl[ch].channel;
	sConfig.Rank = adc_tbl[ch].rank;
	sConfig.SamplingTime = adc_tbl[ch].sampling_time;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&hadc1);

	if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
	{
		Error_Handler();
	}
	ret = HAL_ADC_GetValue(&hadc1);
	adc_data[ch] = ret;
  HAL_ADC_Stop(&hadc1);

	return ret;
}








void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA4     ------> ADC1_IN4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA4     ------> ADC1_IN4
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}



/**
  * @brief  ADC error callback in non blocking mode
  *        (ADC conversion with interruption or transfer by DMA)
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* In case of ADC error, call main error handler */
  Error_Handler();
}

