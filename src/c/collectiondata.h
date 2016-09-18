#pragma once

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

MEASUREMENTS getStats();