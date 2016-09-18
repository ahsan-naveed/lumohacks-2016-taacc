#pragma once
#include <pebble.h>

enum Motion
{
  SAGITAL,
  TANGENT_OF_A_LINE,
  EASY_OVER,
  UNDERCOOKED
};

typedef struct MEASUREMENTS
{
  int range;
  int angle;
  enum Motion motion;
} MEASUREMENTS;

MEASUREMENTS data_collected[2];

MEASUREMENTS getStats();

void hold_still();

//Make sure to change this to what Amir is sending you
//Placeholder function
MEASUREMENTS data_collection();

//Get preop mobility
//void motion_testing_preop();

//Main mobility testing logic
//void motion_testing_postop();


void perform_movement();