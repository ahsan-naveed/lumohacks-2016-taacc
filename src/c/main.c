#include <pebble.h>
 
static Window* window;
static TextLayer *accel_layer;

static void window_load(Window *window)
{
 //Setup Accel Layer
accel_layer = text_layer_create(GRect(5, 45, 144, 30));
text_layer_set_font(accel_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
text_layer_set_text(accel_layer, "Accel tap: N/A");
layer_add_child(window_get_root_layer(window), text_layer_get_layer(accel_layer));
}
 
static void window_unload(Window *window)
{
 text_layer_destroy(accel_layer);
}
static void accel_raw_handler(AccelData *data, uint32_t num_samples)
{
  static char buffer[] = "XYZ: 9999 / 9999 / 9999";
  snprintf(buffer, sizeof("XYZ: 9999 / 9999 / 9999"), "XYZ: %d / %d / %d", data[0].x, data[0].y, data[0].z);
  text_layer_set_text(accel_layer, buffer);
}
 
static void init()
{
  window = window_create();
  WindowHandlers handlers = {
    .load = window_load,
    .unload = window_unload
  };
  window_set_window_handlers(window, (WindowHandlers) handlers);
  window_stack_push(window, true);
  //Subscribe to AccelerometerService (uncomment one to choose)
//accel_tap_service_subscribe(accel_tap_handler);
accel_data_service_subscribe(1, accel_raw_handler);
}
 
static void deinit()
{
  window_destroy(window);
}
 
int main(void)
{
  init();
  app_event_loop();
  deinit();
}

