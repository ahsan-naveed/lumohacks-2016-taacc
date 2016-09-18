#pragma once
#include <pebble.h>



enum DataKey{
  ANGLE_DATA = 0x0, //TUPLE_INT
  ARC_LENGTH = 0x1, //TUPLE_INT
  ACCEL_DATA = 0x2  //TUPLE_INT
};

bool comm_is_js_ready();
void send_collected_data();

//Messaging Handlers
//void message_inbox_received(DictionaryIterator *iterator, void *context);
void message_inbox_received();
void message_inbox_dropped(AppMessageResult reason, void *context);
void message_outbox_sent(DictionaryIterator *iterator, void *context);
void message_outbox_failed(DictionaryIterator *iterator, AppMessageResult reason, void *context);