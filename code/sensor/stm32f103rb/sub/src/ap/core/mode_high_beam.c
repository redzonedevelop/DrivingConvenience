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
   sensor_info.mode[STM_SUBORDINATE].mode_high_beam = HIGH_BEAM_MODE_OFF;
   high_beam_count = 0;
}

void set_mode_high_beam()
{
   if (!sensor_info.error_flag.darkness_error)
   {
      if (get_sensor_darkness())
      {
         sensor_info.mode[STM_SUBORDINATE].mode_high_beam = HIGH_BEAM_MODE_ON;
      }
      else
      {
         sensor_info.mode[STM_SUBORDINATE].mode_high_beam = HIGH_BEAM_MODE_OFF;
      }
   }
}

uint8_t get_mode_high_beam(int board)
{
   return sensor_info.mode[board].mode_high_beam;
}

