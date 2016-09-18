#include <pebble.h>
#include "datacollection.h"
#include "datatransmission.h"
#include "math.h"

#define PI 3.14159265

static bool MOVEMENT_END_STATE = false;
static int meas_idx = 0;

int int_itr = 0;

void hold_still(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Waiting for movement to stop");
  psleep(3000);
}


//Proper implementation when Amir gets his data through
int data_collection(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Performing data collection");
  MEASUREMENTS temp = getStats();
  return temp.angle;
}

//Calculate the arc length of movement
int calculateRange(int angle)
{
  int radians = angle * PI / 180;
  int ran = 2 * PI * radians;
  return(ran);
}

// Calculate the angle that is seen at the first position
int calculateAngle()
{
  int angle = 0;
  CompassHeadingData data;
  compass_service_peek(&data);
  angle = TRIGANGLE_TO_DEG(TRIG_MAX_ANGLE - data.magnetic_heading);
  return(angle);
}

MEASUREMENTS getStats()
{
  MEASUREMENTS stats;
  enum Motion movement = EASY_OVER;
  stats.angle = calculateAngle();
  stats.range = calculateRange(stats.angle);
  stats.motion = movement; // Definitely want to change this bad boy
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "angle %d, range %d", stats.angle, stats.range);
  return(stats);
}

void perform_movement(){
  int temp;
  while(int_itr < 6 && !MOVEMENT_END_STATE){
    if(int_itr < 6 && !MOVEMENT_END_STATE){
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Performing movement %d", int_itr);
      hold_still();
      
      data_collected = data_collection();
      temp = data_collected;
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Angle Value Collected: %d", temp);
      
      vibes_short_pulse();
      if(meas_idx == 1){
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Entered int_itr mod 2 if statement");
        send_collected_data();
        meas_idx = 0;
      }
      int_itr++;
    }
    else{
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Finished performing movements");
      persist_write_bool(1,true);
      MOVEMENT_END_STATE = true;
    }
  }
  int_itr = 0;
}