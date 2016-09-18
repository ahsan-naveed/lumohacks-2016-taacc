#include "pebble.h"
#include "CollectionData.h"
#include "math.h"


#define PI 3.14159265


int calculateRange(int angle)
{
  int radians = angle * PI / 180;
  int ran = 2 * PI * radians;
  return(ran);
}

int calculateAngle()
{
  int angle = 0;
  
  CompassHeadingData data;
  compass_service_peek(&data);
  
  angle = TRIGANGLE_TO_DEG(TRIG_MAX_ANGLE - data.magnetic_heading);
  return(angle);
}

measurements getStats()
{
  measurements stats;
  enum Motion movement = EASY_OVER;
  stats.angle = calculateAngle();
  stats.range = calculateRange(stats.angle);
  stats.motion = movement; // Definitely want to change this bad boy
  APP_LOG(APP_LOG_LEVEL_DEBUG, "angle %d, range %d", stats.angle, stats.range);
  return(stats);
}
