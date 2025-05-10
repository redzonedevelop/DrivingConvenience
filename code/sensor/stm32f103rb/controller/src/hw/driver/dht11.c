/*
 * dht11.c
 *
 *  Created on: May 10, 2025
 *      Author: jeff1
 */


#include "dht11.h"

#define DHT_PORT GPIOB
#define DHT_PIN GPIO_PIN_5

void dwtInit(void)
{
    // Enable TRC (Trace)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // Reset cycle counter
    DWT->CYCCNT = 0;
    // Enable the cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    // 변환: µs → 클럭 사이클
    uint32_t cycles = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT - start) < cycles);
}

void dht11Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	 HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_RESET);
	 /*Configure GPIO pin : DHT11_Pin */
	 GPIO_InitStruct.Pin = DHT_PIN;
	 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init(DHT_PORT, &GPIO_InitStruct);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

int DHT_GetData (DHT_DataTypedef *DHT_Data)
{
    // BUFFER TO RECEIVE
	//Rh_byte1 Rh_byte2 Temp_byte1 Temp_byte2 CHKSUM
    uint8_t bits[5]={0,0,0,0,0};
    uint8_t cnt = 7;
    uint8_t idx = 0;

    // EMPTY BUFFER
    for (int i=0; i< 5; i++) bits[i] = 0;

    // REQUEST SAMPLE
    Set_Pin_Output (DHT_PORT, DHT_PIN);
    HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, GPIO_PIN_RESET);
    HAL_Delay(20); //wait 20ms
    HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, GPIO_PIN_SET);
    delay_us(40);		//wait 20us
    Set_Pin_Input(DHT_PORT, DHT_PIN);

    // ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	// wait for the pin to go low
	while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
	{
		if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
	}
	delay_us(80);
	loopCnt = 1000;
	// wait for the pin to go High
	while (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
	{
		if (loopCnt-- == 0)
			return DHTLIB_ERROR_TIMEOUT;
	}
	delay_us(80);

    // READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
    for (int i=0; i<40; i++)
    {
        loopCnt = 10000;
        while(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN) == GPIO_PIN_RESET){
        	if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
        }


		delay_us(30);
		// if pin is high then 1 or 0
		if (HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))
		{
			bits[idx] |= (1 << cnt);
			delay_us(40);
		}

        if (cnt == 0)   // next byte?
        {
            cnt = 7;    // restart at MSB
            idx++;      // next byte!
        }
        else cnt--;
    }

    // WRITE TO RIGHT VARS
        // as bits[1] and bits[3] are allways zero they are omitted in formulas.
//    float humidity;
//    float temperature;

//    humidity    = bits[0];
//    temperature = bits[2];

    uint8_t sum = bits[0]+bits[1]+bits[2]+bits[3];

    if (bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;

	DHT_Data->Temperature = (int)bits[0];
	DHT_Data->Humidity = (int)bits[2];

    return DHTLIB_OK;
}


