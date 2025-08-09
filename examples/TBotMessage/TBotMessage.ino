#include "WiFi.h"
#include "TelegramBot.h"

TelegramBot TBot;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA); 
  WiFi.begin("XXXXXXX", "XXXXXXXXX");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  TBot.init("KJLHjkluiogUGoiuasiugipauinuuphxhohn78yhwsd", "-XXXXXXXXXXX");
  TBot.send("<b>Привет!<b><tg-spoiler>Это был секретик</tg-spoiler>");
}

void loop() {


}
