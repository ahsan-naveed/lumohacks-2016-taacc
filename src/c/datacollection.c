#include <pebble.h>
#include "datacollection.h"
#include "datatransmission.h"

static bool MOVEMENT_END_STATE = false;

int int_itr = 0;

void hold_still(){
  psleep(3000);
}


//Proper implementation when Amir gets his data through
int data_collection(){
  return 42;
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
}