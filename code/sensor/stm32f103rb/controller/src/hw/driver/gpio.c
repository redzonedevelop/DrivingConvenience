/*
 * gpio.c
 *
 *  Created on: May 11, 2025
 *      Author: hong
 */


#include "gpio.h"
#include "cli.h"






const gpio_tbl_t gpio_tbl[GPIO_MAX_CH] =
    {
        {GPIOB, GPIO_PIN_5,  _DEF_INPUT, GPIO_PIN_RESET, GPIO_PIN_SET,   true},       // 0. SD CD
        {GPIOA, GPIO_PIN_8,  _DEF_INPUT,       GPIO_PIN_SET,   GPIO_PIN_RESET, _DEF_LOW},   // 1. RAIN
    };



#ifdef _USE_HW_CLI
static void cli_gpio(cli_args_t *args);
#endif



bool gpio_init(void)
{
	bool ret = true;


	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	for (int i=0; i<GPIO_MAX_CH; i++)
	{
		gpio_pin_mode(i, gpio_tbl[i].mode);
		gpio_pin_write(i, gpio_tbl[i].init_value);
	}

#ifdef _USE_HW_CLI
	cliAdd("gpio", cli_gpio);
#endif

	return ret;
}

bool gpio_pin_mode(uint8_t ch, uint8_t mode)
{
	bool ret = true;
	GPIO_InitTypeDef GPIO_InitStruct = {0};


	if (ch >= GPIO_MAX_CH)
	{
		return false;
	}

	switch(mode)
	{
		case _DEF_INPUT:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;

		case _DEF_INPUT_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;

		case _DEF_INPUT_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;

		case _DEF_OUTPUT:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;

		case _DEF_OUTPUT_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;

		case _DEF_OUTPUT_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;

	}

	GPIO_InitStruct.Pin = gpio_tbl[ch].pin;
	HAL_GPIO_Init(gpio_tbl[ch].port, &GPIO_InitStruct);

	return ret;
}

void gpio_pin_write(uint8_t ch, bool value)
{
	if (ch >= GPIO_MAX_CH)
	{
		return;
	}

	if (value)
	{
		HAL_GPIO_WritePin(gpio_tbl[ch].port, gpio_tbl[ch].pin, gpio_tbl[ch].on_state);
	}
	else
	{
		HAL_GPIO_WritePin(gpio_tbl[ch].port, gpio_tbl[ch].pin, gpio_tbl[ch].off_state);
	}
}

bool gpio_pin_read(uint8_t ch)
{
  bool ret = false;

  if (ch >= GPIO_MAX_CH)
  {
    return false;
  }

  if (HAL_GPIO_ReadPin(gpio_tbl[ch].port, gpio_tbl[ch].pin) == gpio_tbl[ch].on_state)
  {
    ret = true;
  }

  return ret;
}

void gpio_pin_toggle(uint8_t ch)
{
  if (ch >= GPIO_MAX_CH)
  {
    return;
  }

  HAL_GPIO_TogglePin(gpio_tbl[ch].port, gpio_tbl[ch].pin);
}






#ifdef _USE_HW_CLI
void cli_gpio(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "show") == true)
  {
    while(cliKeepLoop())
    {
      for (int i=0; i<GPIO_MAX_CH; i++)
      {
        cliPrintf("%d", gpio_pin_read(i));
      }
      cliPrintf("\n");
      delay(100);
    }
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "read") == true)
  {
    uint8_t ch;

    ch = (uint8_t)args->getData(1);

    while(cliKeepLoop())
    {
      cliPrintf("gpio read %d : %d\n", ch, gpio_pin_read(ch));
      delay(100);
    }

    ret = true;
  }

  if (args->argc == 3 && args->isStr(0, "write") == true)
  {
    uint8_t ch;
    uint8_t data;

    ch   = (uint8_t)args->getData(1);
    data = (uint8_t)args->getData(2);

    gpio_pin_write(ch, data);

    cliPrintf("gpio write %d : %d\n", ch, data);
    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("gpio show\n");
    cliPrintf("gpio read ch[0~%d]\n", GPIO_MAX_CH-1);
    cliPrintf("gpio write ch[0~%d] 0:1\n", GPIO_MAX_CH-1);
  }
}
#endif
