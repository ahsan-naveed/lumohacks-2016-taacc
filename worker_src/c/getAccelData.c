#include <pebble_worker.h>
//#include "getAccelData.h"
#include <pebble.h>

typedef struct vector3d
  {
  double x;
  double y;
  double z;
} vector3d;

typedef struct measurements
  {
  vector3d position;
  vector3d velocity;
} measurements;

static void accel_data_handler(AccelData *data, measurements *stats, uint32_t num_samples) 
  {
  stats->position.x = 3;//data[0].x;
  stats->position.y = 3;//data[0].y;
  stats->position.z = 3;//data[0].z;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "%f, %f, %f", stats->position.z,stats->position.y,stats->position.x);
}

