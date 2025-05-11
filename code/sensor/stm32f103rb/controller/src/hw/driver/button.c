/*
 * button.c
 *
 *  Created on: May 10, 2025
 *      Author: hong
 */



#include "button.h"
#include "cli.h"

#define BUTTON_DEBOUNCE_MS   20   // 디바운스 타임(ms)


button_tbl_t button_tbl[BUTTON_MAX_CH] =
    {
    	  { GPIOB, GPIO_PIN_3, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET }
    };

static GPIO_PinState  button_last_raw[BUTTON_MAX_CH];
static GPIO_PinState  button_stable[BUTTON_MAX_CH];
static uint32_t       button_last_time[BUTTON_MAX_CH];


#ifdef _USE_HW_CLI
static void cli_button(cli_args_t *arg);
#endif


bool button_init(void)
{
	bool ret = true;
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();


  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  for (int ch =0; ch<BUTTON_MAX_CH; ch++)
  {
    GPIO_InitStruct.Pin = button_tbl[ch].pin;
    HAL_GPIO_Init(button_tbl[ch].port, &GPIO_InitStruct);

    button_last_raw[ch]   = button_tbl[ch].off_state;
    button_stable[ch]     = button_tbl[ch].off_state;
    button_last_time[ch]  = HAL_GetTick();
    button_tbl[ch].current_state = button_tbl[ch].off_state;
  }


#ifdef _USE_HW_CLI
  cliAdd("button", cli_button);
#endif

  return ret;
}

GPIO_PinState button_get_state(uint8_t ch)
{

	if (ch >= BUTTON_MAX_CH) Error_Handler();

	  uint32_t now = HAL_GetTick();
	  GPIO_PinState raw = HAL_GPIO_ReadPin(button_tbl[ch].port, button_tbl[ch].pin);

	  if (raw != button_last_raw[ch])
	  {
	    button_last_time[ch]  = now;
	    button_last_raw[ch]   = raw;
	  }
	  // (2) raw가 안정 상태(stable)를 유지하면
	  else if ((now - button_last_time[ch]) > BUTTON_DEBOUNCE_MS)
	  {
	    if (button_stable[ch] != raw)
	    {
	      button_stable[ch] = raw;

	      if (raw == button_tbl[ch].on_state)
	      {
	        button_tbl[ch].current_state =
	          (button_tbl[ch].current_state == button_tbl[ch].on_state)
	            ? button_tbl[ch].off_state
	            : button_tbl[ch].on_state;
	      }
	    }
	  }

	  return button_tbl[ch].current_state;
}



#ifdef _USE_HW_CLI
void cli_button(cli_args_t *args)
{
	bool ret = false;

	if (args->argc == 1 && args->isStr(0, "show") == true)
	{
		while(cliKeepLoop())
		{
			for (int i=0; i<BUTTON_MAX_CH; i++)
			{
				cliPrintf("%d", button_get_state(i));
			}
			cliPrintf("\n");
			delay(100);
		}
		ret = true;
	}

	if (ret != true)
	{
		cliPrintf("button show\n");
	}
}


#endif
