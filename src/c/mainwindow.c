#include <pebble.h>
#include "mainwindow.h"
#include "instructionwindow.h"

TextLayer *s_main_text;
Window *s_main_window;

void main_window_load(Window *window){
  //Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
  //Create the text layer with specified bounds
  s_main_text = text_layer_create(GRect(0,0,144,154));
  text_layer_set_background_color(s_main_text, GColorClear);
  text_layer_set_text_color(s_main_text, GColorBlack);
  text_layer_set_text(s_main_text, "Hi! Let's check your arm motion today.\n\n Open up the app in your phone!");
  text_layer_set_font(s_main_text, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_main_text, GTextAlignmentCenter);
  
  //Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_main_text));
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Main window loaded");
}

void main_window_unload(Window *window){
  //Destroy the text layer
  text_layer_destroy(s_main_text);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Main Window Unloaded");
}
