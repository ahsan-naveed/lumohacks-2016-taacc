#include <pebble.h>
#include "CollectionData.h"

#include <pebble.h>
#include <math.h>
#include <windows.h>

#define PI 3.14159265


int calculateRange(int angle)
{
  int radians = angle * PI / 180;
  int ran = 2 * PI * radians;
  return(ran);
}

int calculateAngle()
{
  int angle1 = 0;
  int angle2 = 0;
  int differenceAngle = 0;
  
  CompassHeadingData data;
  compass_service_peek(&data);
  
  //grab angle 1
  angle1 = TRIGANGLE_TO_DEG(TRIG_MAX_ANGLE - data.magnetic_heading);
  
  Sleep(1);
  
  angle2 = TRIGANGLE_TO_DEG(TRIG_MAX_ANGLE - data.magnetic_heading);
  
  differenceAngle = angle2-angle1;
  return(differenceAngle);
}

void getStats(measurements *stats)
{
  Motion = movement;
  stats->angle = calculateAngle();
  stats->range = calculateRange(stats.angle);
  stats->motion = movement[1]; // Definitely want to change this bad boy
  APP_LOG(APP_LOG_LEVEL_DEBUG, "angle %d, range %d", stats->angle, stats->range);
}