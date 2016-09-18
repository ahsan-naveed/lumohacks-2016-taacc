#include <pebble.h>

static Window *s_main_window;
static Window *s_instruction_window;
static TextLayer *s_main_text;
static TextLayer *s_instruction_text;

static void main_window_load(Window *window){
  //Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
  //Create the text layer with specified bounds
  s_main_text = text_layer_create(GRect(0,0,144,154));
  
  //Make it more like a watch face
  text_layer_set_background_color(s_main_text, GColorClear);
  text_layer_set_text_color(s_main_text, GColorBlack);
  text_layer_set_text(s_main_text, "Hi! Let's check your arm motion today.\n\n Open up the app in your phone!");
  text_layer_set_font(s_main_text, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_main_text, GTextAlignmentCenter);
  
  //Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_main_text));
}

static void main_window_unload(Window *window){
  //Destroy the text layer
  text_layer_destroy(s_main_text);
}

static void inst_window_load(Window *window){
  
  //Create layer with all bounds
  s_main_text = text_layer_create(GRect(0,0,144,154));
  text_layer_set_background_color(s_main_text, GColorClear);
  text_layer_set_text_color(s_main_text, GColorBlack);
  text_layer_set_text(s_main_text, "Whenever you feel the watch buzz, look to your phone for the next movement.\n Let's start by letting your arm hand below you.");
  text_layer_set_font(s_main_text, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_main_text, GTextAlignmentCenter);
  
}

static void inst_window_unload(Window *window){
  //Destroy text layer
  text_layer_destroy(s_instruction_text);
}

static void main_window_click_handler(ClickRecognizerRef recognizer, void *context){
  Window *newWindow = (Window*) context;
  if(newWindow == s_main_window){
    window_stack_push(s_instruction_window, true);
  }
  else if(newWindow == s_instruction_window){
    window_stack_pop(false);
    window_stack_pop(false);
  }
  else{
    APP_LOG(APP_LOG_LEVEL_DEBUG, "ERROR: Wrong context. Did you select the right window?");
  }
  window_stack_push(s_instruction_window, true);
}

static void main_window_click_provider(Window *window){
  //All button UP clicks will map to the same function to go to the next window
  window_single_click_subscribe(BUTTON_ID_DOWN, main_window_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 1000, main_window_click_handler);
  window_multi_click_subscribe(BUTTON_ID_DOWN, 2, 4, 3000, false, main_window_click_handler);
  window_long_click_subscribe(BUTTON_ID_DOWN, 700, main_window_click_handler, main_window_click_handler);
}

static void init(){
  //Create main window element and assign it to the pointer
  s_main_window = window_create();
  s_instruction_window = window_create();
  
  //Set handlers to manage the elements inside the window
  window_set_window_handlers(s_main_window, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_window_handlers(s_instruction_window,(WindowHandlers){
    .load = inst_window_load,
    .unload = inst_window_unload
  });
  
  //Show the window on the watch
  window_stack_push(s_main_window, true);
  
  //Register click provider callback
  window_set_click_config_provider(s_main_window, (ClickConfigProvider) main_window_click_provider);
}

static void deinit(){
  //Destroy window
  window_destroy(s_main_window);
  window_destroy(s_instruction_window);
}

int main(void){
  init();
  app_event_loop();
  deinit();
}