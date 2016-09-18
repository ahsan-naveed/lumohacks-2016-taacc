#include <pebble.h>
#include "datatransmission.h"
#include "datacollection.h"
#define ORIGINAL_DATA_COLLECTION_KEY 0
#define MESSAGE_KEY_JSReady 0


//Set bool to indicate whether or not JS is ready
static bool s_js_ready = false; 
extern int int_itr;
//Return js comm status
bool comm_is_js_ready(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Comms boolean reports ready");
  return s_js_ready;
}

void send_collected_data(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending Angle %d", data_collected);
  /*APP_LOG(APP_LOG_LEVEL_DEBUG, "Entering send_collected_data");
  DictionaryIterator *outmsg_iter;
  int original_flag = 0;
  
  AppMessageResult result = app_message_outbox_begin(&outmsg_iter);
  
  if(result == APP_MSG_OK){
    if(persist_exists(ORIGINAL_DATA_COLLECTION_KEY)){
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending first set of data collection (preop)");
      original_flag = 1;
      dict_write_int(outmsg_iter, 0, &original_flag, 1, false);
      dict_write_int(outmsg_iter, int_itr, &data_collected[int_itr], 4, true);
    }
    else{
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending set of data collection (postop)");
      dict_write_int(outmsg_iter, 0, &original_flag, 1, false);
      dict_write_int(outmsg_iter, int_itr, &data_collected[int_itr], 4, true);
    }
    
    //Send the message
    result = app_message_outbox_send();
    if(result != APP_MSG_OK){
      APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending the outbox: %d", result);
    }
  }
  else{
    //Outbox cannot be used at the moment
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Error preparing the outbox: %d", result);
  }*/
}

/*
void message_inbox_received(DictionaryIterator *iterator, void *context){
  Tuple *ready_tuple = dict_find(iterator, MESSAGE_KEY_JSReady);
  if(ready_tuple){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "PebbleKit JS is ready");
    s_js_ready = true;
    perform_movement();
  }  
}*/

//Placeholder for above
void message_inbox_received(){
  if(true){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "PebbleKit is ready");
    s_js_ready = true;
    perform_movement();
  }
}

void message_inbox_dropped(AppMessageResult reason, void *context){
   APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped for reason: %d", reason);
}

void message_outbox_failed(DictionaryIterator *iterator, AppMessageResult reason, void *context){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to send for reason: %d", reason);
}