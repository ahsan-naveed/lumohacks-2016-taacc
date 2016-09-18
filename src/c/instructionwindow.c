#include <pebble.h>
#include "instructionwindow.h"
#include "testingwindow.h"

Window *s_instruction_window;
TextLayer *s_instruction_text;



void inst_window_load(Window *window){
  //Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
  //Create layer with all bounds
  s_instruction_text = text_layer_create(GRect(0,0,144,154));
  text_layer_set_background_color(s_instruction_text, GColorClear);
  text_layer_set_text_color(s_instruction_text, GColorBlack);
  text_layer_set_text(s_instruction_text, "Let's start by having your arm hang below you. Look at your phone for the next movement");
  text_layer_set_font(s_instruction_text, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_instruction_text, GTextAlignmentCenter);
  
  //Add instruction_text as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_instruction_text));
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Instruction Window Loaded");
}



void inst_window_unload(Window *window){
  //Destroy text layer
  text_layer_destroy(s_instruction_text);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Instruction Window Unloaded");
}