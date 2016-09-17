#include <pebble.h>

static Window *s_main_window;//Pointer to new pebble watch window
static TextLayer *s_time_layer;//Create a text layer


static void main_window_load(Window *window){
  //Get window information
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  //Create a new textlayer with specified bounds
  s_time_layer = text_layer_create(
    GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  
  //Make the layout a bit more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  //Add as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window){
  //Destroy the text layer
  text_layer_destroy(s_time_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  
}

static void init(Window *window){
  //Create main Window element and assign it to the global pointer
  s_main_window = window_create();
  
  //Register with TickTimerserver
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //Setting handlers to manage elements within the window
  window_set_window_handlers(s_main_window, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  //Show the window on the watch with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit(Window *window){
  //Destroy the window
  window_destroy(s_main_window);
}

int main(void){
  init(s_main_window);
  app_event_loop();//Event loop, app will wait for system event
  deinit(s_main_window);
}