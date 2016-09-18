#pragma once
#include <pebble.h>

extern TextLayer *s_test_text;
extern Window *s_test_window;

void test_window_load(Window *window);
void test_window_unload(Window *window);
void persistent_storage_decision();