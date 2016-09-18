#pragma once
#include <pebble.h>
#include "collectiondata.h"


MEASUREMENTS data_collected[2];

void hold_still();

//Make sure to change this to what Amir is sending you
//Placeholder function
MEASUREMENTS data_collection();

//Get preop mobility
//void motion_testing_preop();

//Main mobility testing logic
//void motion_testing_postop();


void perform_movement();