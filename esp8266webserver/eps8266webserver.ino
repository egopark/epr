#include <ESP8266WiFi.h>

const char* ssid     = "ssid";
const char* password = "password";


void setup() {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
    if (WiFi.status() != WL_CONNECTED)
  {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
  }
}
