/*
 * led.c
 *
 *  Created on: May 2, 2025
 *      Author: hong
 */


#include "led.h"
#include "cli.h"


typedef struct
{
	GPIO_TypeDef *port;
	uint16_t      pin;
	GPIO_PinState on_state;
	GPIO_PinState off_state;
} led_tbl_t;

led_tbl_t led_tbl[LED_MAX_CH] =
		{
			{GPIOA, GPIO_PIN_5, GPIO_PIN_RESET, GPIO_PIN_SET},

		};


#ifdef _USE_HW_CLI
static void cliLed(cli_args_t *args);
#endif




bool led_init(void)
{
	bool ret = true;

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  for (int i=0; i<LED_MAX_CH; i++)
  {
    GPIO_InitStruct.Pin = led_tbl[i].pin;
    HAL_GPIO_Init(led_tbl[i].port, &GPIO_InitStruct);

  	led_off(i);
  }

#ifdef _USE_HW_CLI
  cliAdd("led", cliLed);
#endif

	return ret;
}

void led_on(uint8_t ch)
{
	if(ch >= LED_MAX_CH) return;

  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].on_state);

}

void led_off(uint8_t ch)
{
	if(ch >= LED_MAX_CH) return;

  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].off_state);
}

void led_toggle(uint8_t ch)
{
	if(ch >= LED_MAX_CH) return;

	HAL_GPIO_TogglePin(led_tbl[ch].port, led_tbl[ch].pin);

}


#ifdef _USE_HW_CLI
void cliLed(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 3 && args->isStr(0, "toggle") == true)
  {
    uint8_t  led_ch;
    uint32_t toggle_time;
    uint32_t pre_time;

    led_ch      = args->getData(1);
    toggle_time = args->getData(2);

    if (led_ch > 0)
    {
      led_ch--;
    }

    pre_time = millis();
    while(cliKeepLoop())
    {
      if (millis()-pre_time >= toggle_time)
      {
        pre_time = millis();
        led_toggle(led_ch);
      }
    }
    ret = true;
  }



  if (ret != true)
  {
    cliPrintf("led toggle ch[1~%d] time(ms)\n", LED_MAX_CH);
  }
}
#endif


