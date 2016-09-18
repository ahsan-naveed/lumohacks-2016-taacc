#pragma once
#include <pebble.h>

extern TextLayer *s_instruction_text;
extern Window *s_instruction_window;

void inst_window_load(Window *window);
void inst_window_unload(Window *window);
