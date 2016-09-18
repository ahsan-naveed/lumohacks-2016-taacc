#pragma once
#include <pebble.h>

extern TextLayer *s_main_text;
extern Window *s_main_window;

void main_window_load(Window *window);
void main_window_unload(Window *window);
