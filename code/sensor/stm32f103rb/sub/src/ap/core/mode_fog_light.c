/*
 * mode_fog_light.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_fog_light.h"
#include "sensor.h"

int fog_light_count;

void mode_fog_light_init()
{
   sensor_info.mode[STM_SUBORDINATE].mode_fog_light = FOG_LIGHT_MODE_OFF;
   fog_light_count = 0;
}

void set_mode_fog_light()
{
   if (!sensor_info.error_flag.humidity_error)
   {
      if (get_sensor_humidity() > 25)
      {
         sensor_info.mode[STM_SUBORDINATE].mode_fog_light = FOG_LIGHT_MODE_ON;
      }
      else
      {
         sensor_info.mode[STM_SUBORDINATE].mode_fog_light = FOG_LIGHT_MODE_OFF;
      }
   }
}

uint8_t get_mode_fog_light(int board)
{
   return sensor_info.mode[board].mode_fog_light;
}
