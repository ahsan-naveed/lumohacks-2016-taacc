#pragma once
#include <pebble.h>

enum DataKey{
  ANGLE_DATA = 0x0, //TUPLE_INT
  ARC_LENGTH = 0x1, //TUPLE_INT
  ACCEL_DATA = 0x2  //TUPLE_INT
};

bool comm_is_js_ready();