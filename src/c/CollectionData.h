#pragma once

enum Motion
{
  SAGITAL,
  TANGENT_OF_A_LINE,
  EASY_OVER,
  UNDERCOOKED
};

struct measurements
{
  int range;
  int angle;
  Motion motion;
};
