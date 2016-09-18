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

int data_collected;

MEASUREMENTS getStats();

void hold_still();

//Make sure to change this to what Amir is sending you
int data_collection();

void perform_movement();