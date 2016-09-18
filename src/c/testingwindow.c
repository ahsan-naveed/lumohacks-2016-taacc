#include <pebble.h>
#include "testingwindow.h"

TextLayer *s_test_text;
Window *s_test_window;

void test_window_load(Window *window){
  //Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
  //Create layer with all bounds
  s_test_text = text_layer_create(GRect(0,0,144,154));
  text_layer_set_background_color(s_test_text, GColorClear);
  text_layer_set_text_color(s_test_text, GColorBlack);
  text_layer_set_text(s_test_text, "Now watch your phone for instructions.");
  text_layer_set_font(s_test_text, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_test_text, GTextAlignmentCenter);
  
  //Add instruction_text as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_test_text));
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Test Window Loaded");
}

void test_window_unload(Window *window){
  //Destroy the text layer
  text_layer_destroy(s_test_text);
}
