#pragma once

typedef struct vector3d
  {
  double x;
  double y;
  double z;
} vector3d;

typedef struct measurements
  {
  vector3d position;
  vector3d velocity;
} measurements;
