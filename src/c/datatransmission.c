#include <pebble.h>
#include "datatransmission.h"

//Set bool to indicate whether or not JS is ready
static bool s_js_ready = false; 

//Return js comm status
bool comm_is_js_ready(){
  return s_js_ready;
}
