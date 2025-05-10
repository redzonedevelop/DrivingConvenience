/*
 * mode_rain_road.c
 *
 *  Created on: May 10, 2025
 *      Author: eunseo
 */

#include "mode_rain_road.h"
#include "sensor.h"

#define STM_TRANS		0
#define STM_CONTROLELR	1
#define STM_SUBORDINATE	2

int rain_road_count;

void mode_rain_road_init()
{
   sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = RAINROAD_MODE_OFF;
   rain_road_count = 0;
}

void set_mode_rain_road()
{
   if (!sensor_info.error_flag.rain_error)
   {
      if (sensor_info.sensor_value.rain)
      {
         sensor_info.mode[STM_CONTROLELR].mode_rain_road.mode_value = RAINROAD_MODE_ON;
      }
      else
      {
         sensor_info.mode[STM_CONTROLELR].mode_rain_road.mode_value = RAINROAD_MODE_OFF;
      }
   }
}

uint8_t get_mode_rain_road(int board)
{
   return sensor_info.mode[board].mode_rain_road.mode_value;
}

void compare_mode_rain_road()
{
   if (!sensor_info.error_flag.rain_error)
   {
      if (get_mode_rain_road(STM_CONTROLELR) == get_mode_rain_road(STM_SUBORDINATE))
      {
         sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = get_mode_rain_road(STM_CONTROLELR);
         if (rain_road_count > 0)
            rain_road_count--;
      }
      else
      {
         rain_road_count++;
         if (rain_road_count > 7)
         {
            sensor_info.error_flag.rain_error = true;
            sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = RAINROAD_MODE_ERROR;
         }
      }
   }
   else
   {
      sensor_info.mode[STM_TRANS].mode_rain_road.mode_value = RAINROAD_MODE_ERROR;
   }
}
