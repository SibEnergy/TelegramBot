/*
  TelegramMess.cpp - Library for sending messages to telegram chat
  Created by Oleg N. Andrianov, August 6, 2025.
  Released into the public domain.
*/

#include <Arduino.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>
#include "TelegramMess.h"
HTTPClient https;


void TelegramMess::init(char* Token, char* Chat_ID){
	str_All=String(str_before_token)+String(Token)+String(str_after_token)+String(Chat_ID)+String(str_after_chat_id);
}


void TelegramMess::send(char* Message){
String str_Full;
str_Full=str_All+String(Message);
Serial.println(str_All);

NetworkClientSecure *client = new NetworkClientSecure;
Serial.println("Make client");

  if (client) {
Serial.println("Client created");
    client->setCACert(root_ca);
Serial.println("Client get sertificate");
    {  
      Serial.print("[HTTPS] begin...\n");
	if (https.begin(*client, str_Full)) {  // HTTPS
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET code: %d\n", httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTPS] GET failed, error: %s\n", https.errorToString(httpCode).c_str());
        }

        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }

      // End extra scoping block
    }

    delete client;
  } else {
    Serial.println("Unable to create client");
  }

}

