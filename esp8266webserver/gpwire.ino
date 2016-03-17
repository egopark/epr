#include "Arduino.h"
#include <Wire.h> 

const int pinNumberSDA      = 2;
const int pinNumberSCL      = 0;
const int wireClock         = 1000;
const char wireAdress       = 32;// B100000; //= B100000 = 32; /* address range  B100000 to B100111 */

char output;

void InitWire()
{
  output =0;
  Wire.begin(pinNumberSDA, pinNumberSCL);    //begin(int sda, int scl) GPIO Pins, change to  Wire.begin(); for not ESP8266
  Wire.setClock(wireClock);
  Wire.requestFrom(wireAdress, 1);    // 
  while (Wire.available()){
    int i = Wire.read(); // receive a byte as character
  }
  WireTransmission();
}

void WireTransmission()
{
  Wire.beginTransmission(wireAdress);
  Wire.write(~output);
  Wire.endTransmission();
}
