#include <pebble.h>
#include "datacollection.h"
#include "datatransmission.h"
#include "math.h"

#define PI 3.14159265

static bool MOVEMENT_END_STATE = false;

int int_itr = 0;

void hold_still(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Waiting for movement to stop");
  psleep(3000);
}


//Proper implementation when Amir gets his data through
MEASUREMENTS data_collection(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Performing data collection");
  return getStats();
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


/*//Main logic
void motion_testing_postop(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Entering postop motion testing");
  //Wait for arm to stop moving
  hold_still();
  
  //Store initial values
  data_collected[0] = data_collection();
  
  //Motion tracking indication for loop
  for(int i = 1; i < 7; i += 2){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Arm up position");
    //Indicate upwards arm movement
    vibes_short_pulse();
    //Wait for arm to stop moving
    hold_still();
    //Collect data in the up position
    data_collected[i] = data_collection();
    
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Arm down position");
    //Indicate downwards arm movement
    vibes_short_pulse();
    //Wait for arm to stop moving
    hold_still();
    //Collect data in neutral arm position
    data_collected[i+1] = data_collection();
  } 
}

//Preop testing
void motion_testing_preop(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Entering preop motion testing");
   //Wait for arm to stop moving
  hold_still();
  
  //Store initial values
  data_collected[0] = data_collection();
  
  //Motion tracking indication for loop
  for(int i = 1; i < 7; i += 2){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Arm up position");
    //Indicate upwards arm movement
    vibes_short_pulse();
    //Wait for arm to stop moving
    hold_still();
    //Collect data in the up position
    data_collected[i] = data_collection();
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Arm down position");
    //Indicate downwards arm movement
    vibes_short_pulse();
    //Wait for arm to stop moving
    hold_still();
    //Collect data in neutral arm position
    data_collected[i+1] = data_collection();
  } 
}*/

void perform_movement(){
  if(int_itr < 6 && !MOVEMENT_END_STATE){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Performing movement %d", int_itr);
    hold_still();
    data_collected[int_itr] = data_collection();
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Data collected is: %d %d %d", data_collected[int_itr].angle, data_collected[int_itr].range, data_collected[int_itr].motion);
    vibes_short_pulse();
    if(int_itr % 2 != 0){
      send_collected_data();
    }
    int_itr++;
  }
  else{
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Finished performing movements");
    persist_write_bool(1,true);
    MOVEMENT_END_STATE = true;
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Data collected is: %d %d %d", data_collected[int_itr].angle, data_collected[int_itr].range, data_collected[int_itr].motion);
}