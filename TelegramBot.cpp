/*
  TelegramBot.cpp - Library for sending messages to telegram chat
  Created by Oleg N. Andrianov, August 6, 2025.
  Released into the public domain.
*/

#include "TelegramBot.h"
#include "HTTPClient.h"

HTTPClient http;

TelegramBot::TelegramBot(String Token, String Chat_ID){
	str_All=str_before_token + Token + str_after_token + Chat_ID + str_after_chat_id;
}

void TelegramBot::send(String Message){
    http.begin(All+Message,root_ca); //HTTPS
    int httpCode = http.GET();
    if(httpCode > 0) {// file found at server     
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      } else {// HTTP header has been send and Server response header has been handled        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      }
    } else {// httpCode will be negative on error
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}