#pragma once

enum Motion
{
  SAGITAL,
  TANGENT_OF_A_LINE,
  EASY_OVER,
  UNDERCOOKED
};

typedef struct measurements
{
  int range;
  int angle;
  enum Motion motion;
} measurements;

measurements getStats();