#include <pebble.h>

static Window *s_main_window;//Pointer to new pebble watch window

static void init(){
  
}

static void deinit(){
  
}

int main(void){
  init();
  app_event_loop();//Event loop, app will wait for system event
  deinit();
}