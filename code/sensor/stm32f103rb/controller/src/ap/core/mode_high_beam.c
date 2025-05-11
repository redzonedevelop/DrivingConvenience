/*
 * mode_high_beam.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_high_beam.h"
#include "sensor.h"

#define STM_TRANS		0
#define STM_CONTROLELR	1
#define STM_SUBORDINATE	2

int high_beam_count;

void mode_high_beam_init()
{
   sensor_info.mode[STM_TRANS].mode_high_beam.mode_value = HIGH_BEAM_MODE_OFF;
   high_beam_count = 0;
}

void set_mode_high_beam()
{
   if (!sensor_info.error_flag.darkness_error)
   {
      if (sensor_info.sensor_value.darkness)
      {
         sensor_info.mode[STM_CONTROLELR].mode_high_beam.mode_value = HIGH_BEAM_MODE_ON;
      }
      else
      {
         sensor_info.mode[STM_CONTROLELR].mode_high_beam.mode_value = HIGH_BEAM_MODE_OFF;
      }
   }
}

uint8_t get_mode_high_beam(int board)
{
   return sensor_info.mode[board].mode_high_beam.mode_value;
}

void compare_mode_high_beam()
{
   if (!sensor_info.error_flag.darkness_error)
   {
      if (get_mode_high_beam(STM_CONTROLELR) == get_mode_high_beam(STM_SUBORDINATE))
      {
         sensor_info.mode[STM_TRANS].mode_high_beam.mode_value = get_mode_high_beam(STM_CONTROLELR);
         if (high_beam_count > 0)
            high_beam_count--;
      }
      else
      {
         high_beam_count++;
         if (high_beam_count > 7)
         {
            sensor_info.error_flag.darkness_error = true;
            sensor_info.mode[STM_TRANS].mode_high_beam.mode_value = HIGH_BEAM_MODE_ERROR;
         }
      }
   }
   else
   {
      sensor_info.mode[STM_TRANS].mode_high_beam.mode_value = HIGH_BEAM_MODE_ERROR;
   }
}
