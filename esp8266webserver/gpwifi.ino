#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <IPAddress.h>

const int portNumber = 80;
const char* ssid     = "ssid";
const char* password = "password";
IPAddress ipMyIP      (192, 168,   0,   6);
IPAddress ipGatewayIP (192, 168,   0,   1);
IPAddress ipSubnet    (255, 255, 255,   0);
IPAddress ipDNS       (192, 168,   0,   1);

WiFiServer httpServer(portNumber);


void WiFiStart()
{
  WiFi.begin(ssid, password);
  //set static ip
  WiFi.config(ipMyIP, ipGatewayIP, ipSubnet, ipDNS);

  while (WiFiIsCONNECTED()) {
    delay(500);
  }

  httpServer.begin();
}


void WiFiSetup()
{
  WiFi.mode(WIFI_STA);
  WiFiStart();
}

boolean WiFiIsCONNECTED()
{
  return WiFi.status() != WL_CONNECTED;
}

void WiFiHandleClient()
{
  WiFiClient client = httpServer.available();
  if (client) 
  {
    //TBD
  }
}
