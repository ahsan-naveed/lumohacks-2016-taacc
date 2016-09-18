#include <pebble.h>
#include "mainwindow.h"
#include "instructionwindow.h"
#include "testingwindow.h"
#include "datacollection.h"
#include "datatransmission.h"


void main_window_click_handler(ClickRecognizerRef recognizer, void *context);
void main_window_click_provider(Window *window);
static void init();
static void deinit();

int main(void){
  init();
  app_event_loop();
  deinit();
}


void window_click_handler(ClickRecognizerRef recognizer, void *context){
  if(window_stack_contains_window(s_instruction_window)){
    window_stack_push(s_test_window, true);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushed test window to top");
  }
  else{
    window_stack_push(s_instruction_window, true);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushed instruction window to top");
  }
}

void window_click_provider(Window *window){
  //All button DOWN clicks will map to the same function to go to the next window
  window_single_click_subscribe(BUTTON_ID_DOWN, window_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 1000, window_click_handler);
  window_multi_click_subscribe(BUTTON_ID_DOWN, 2, 4, 3000, false, window_click_handler);
  window_long_click_subscribe(BUTTON_ID_DOWN, 700, window_click_handler, window_click_handler);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Subscribed to clicks");
}


static void init(){
  //Largest expected inbox and outbox message sizes
  const uint32_t inbox_size = 64;
  const uint32_t outbox_size = 256;
  
  //Create main window element and assign it to the pointer
  s_main_window = window_create();
  s_instruction_window = window_create();
  s_test_window = window_create();
  
  //Set handlers to manage the elements inside the window
  window_set_window_handlers(s_main_window, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_window_handlers(s_instruction_window, (WindowHandlers){
    .load = inst_window_load,
    .unload = inst_window_unload
  });
  window_set_window_handlers(s_test_window, (WindowHandlers){
    .load = test_window_load,
    .unload = test_window_unload
  });
  
  //Show the window on the watch
  window_stack_push(s_main_window, true);
  
  //Register click provider callback
  window_set_click_config_provider(s_main_window, (ClickConfigProvider) window_click_provider);
  window_set_click_config_provider(s_instruction_window, (ClickConfigProvider) window_click_provider);
  
  //Open app messaging
  app_message_register_inbox_received(message_inbox_received);
  app_message_register_inbox_dropped(message_inbox_dropped);
  app_message_register_outbox_failed(message_outbox_failed);
  
  app_message_open(inbox_size, outbox_size);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Application Initialized");

}

static void deinit(){
  //Destroy window
  window_destroy(s_main_window);
  window_destroy(s_instruction_window);
  window_destroy(s_test_window);
}