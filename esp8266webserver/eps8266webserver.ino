#include "gpwifi.h"

void setup() {
  WiFiSetup();
  InitWire();
}

void loop() {
  if (WiFiIsCONNECTED())
  {
    WiFiStart();
  }
  WiFiHandleClient();
  WireTransmission();
}
