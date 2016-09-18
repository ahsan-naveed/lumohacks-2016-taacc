#pragma once
#include <pebble.h>


int data_collected[31];

void hold_still();

//Make sure to change this to what Amir is sending you
//Placeholder function
int data_collection();

//Get preop mobility
//void motion_testing_preop();

//Main mobility testing logic
//void motion_testing_postop();


void perform_movement();