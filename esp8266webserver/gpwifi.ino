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
WiFiClient client;
boolean clientConnected = false;
unsigned long timeOfConnect = 0;

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
  if (!clientConnected)
  {
    client = httpServer.available();
    if (client) 
    {
      // new client
      clientConnected = true;
      timeOfConnect = millis();
    } else {
      clientConnected = false;
      timeOfConnect = 0;
    }
  }

  if (clientConnected && client.available())
  {
    String request = client.readStringUntil('\r');
    client.flush();
    // 
    String response;
    String responseHeader;
    String responseContent="<html><head><title>test title</title></head><body>test response</body></html>";

    responseHeader  = "HTTP/1.1 200 OK\r\n";
    responseHeader += "Content-Length: ";
    responseHeader += responseContent.length();
    responseHeader += "\r\n";
    responseHeader += "Content-Type: text/html\r\n";
    responseHeader += "Connection: close\r\n";
    responseHeader += "\r\n";

    response  = responseHeader ;
    response += responseContent;
    client.print(response);
    client.stop();
    clientConnected = false;
    timeOfConnect = 0;
  }

  if (clientConnected && ( (timeOfConnect + 500) > millis() ))
  {
    client.stop();
    clientConnected = false;
    timeOfConnect = 0;
  }

}
