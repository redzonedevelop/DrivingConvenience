/*
 * mode_fog_light.c
 *
 *  Created on: May 10, 2025
 *      Author: USER
 */

#include "mode_fog_light.h"

#define STM_TRANS       0
#define STM_CONTROLELR	1
#define STM_SUBORDINATE 2

int fog_light_count;

void mode_fog_light_init()
{
   sensor_info.mode[STM_TRANS].mode_fog_light = FOG_LIGHT_MODE_OFF;
   fog_light_count = 0;
}

void set_mode_fog_light()
{
   if (!sensor_info.error_flag.humidity_error)
   {
      if (sensor_info.sensor_value.humidity)
      {
         sensor_info.mode[STM_CONTROLELR].mode_fog_light = FOG_LIGHT_MODE_ON;
      }
      else
      {
         sensor_info.mode[STM_CONTROLELR].mode_fog_light = FOG_LIGHT_MODE_OFF;
      }
   }
}

uint8_t get_mode_fog_light(int board)
{
   return sensor_info.mode[board].mode_fog_light;
}

void compare_mode_fog_light()
{
   if (!sensor_info.error_flag.humidity_error)
   {
      if (get_mode_fog_light(STM_CONTROLELR) == get_mode_fog_light(STM_SUBORDINATE))
      {
         sensor_info.mode[STM_TRANS].mode_fog_light = get_mode_fog_light(STM_CONTROLELR);
         if (fog_light_count > 0)
            fog_light_count--;
      }
      else
      {
         fog_light_count++;
         if (fog_light_count > 7)
         {
            sensor_info.error_flag.humidity_error = true;
            sensor_info.mode[STM_TRANS].mode_fog_light = FOG_LIGHT_MODE_ERROR;
         }
      }
   }
   else
   {
      sensor_info.mode[STM_TRANS].mode_fog_light = FOG_LIGHT_MODE_ERROR;
   }
}
