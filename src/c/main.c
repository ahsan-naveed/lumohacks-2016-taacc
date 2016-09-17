#include <pebble.h>

static Window *s_main_window;//Pointer to new pebble watch window

static void init(Window *window){
  
}

static void deinit(Window *window){
  
}

int main(void){
  init(s_main_window);
  app_event_loop();//Event loop, app will wait for system event
  deinit(s_main_window);
}