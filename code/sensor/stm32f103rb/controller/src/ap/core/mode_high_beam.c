/*
 * mode_high_beam.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_high_beam.h"
#include "sensor.h"

int high_beam_count;

void mode_high_beam_init()
{
   sensor_info.mode[STM_TRANS].mode_high_beam = HIGH_BEAM_MODE_OFF;
   high_beam_count = 0;
}

void set_mode_high_beam()
{
   if (!sensor_info.error_flag.darkness_error)
   {
      if (get_sensor_darkness())
      {
         sensor_info.mode[STM_CONTROLLER].mode_high_beam = HIGH_BEAM_MODE_ON;
      }
      else
      {
         sensor_info.mode[STM_CONTROLLER].mode_high_beam = HIGH_BEAM_MODE_OFF;
      }
   }
   esp32_info.mode_high_beam = sensor_info.mode[STM_TRANS].mode_high_beam;
}

uint8_t get_mode_high_beam(int board)
{
   return sensor_info.mode[board].mode_high_beam;
}

void compare_mode_high_beam()
{
   if (!sensor_info.error_flag.darkness_error)
   {
      if (get_mode_high_beam(STM_CONTROLLER) == get_mode_high_beam(STM_SUBORDINATE))
      {
         sensor_info.mode[STM_TRANS].mode_high_beam = get_mode_high_beam(STM_CONTROLLER);
         if (high_beam_count > 0)
            high_beam_count--;
      }
      else
      {
         high_beam_count++;
         if (high_beam_count > 1000)
         {
            sensor_info.error_flag.darkness_error = true;
            sensor_info.mode[STM_TRANS].mode_high_beam = HIGH_BEAM_MODE_ERROR;
         }
      }
   }
   else
   {
      sensor_info.mode[STM_TRANS].mode_high_beam = HIGH_BEAM_MODE_ERROR;
   }
}
