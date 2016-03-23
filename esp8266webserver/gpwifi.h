//gpwifi.h
#include "Arduino.h"
 
#ifndef HEADER_GPWIFI
  #define HEADER_GPWIFI

  void WiFiStart( void );
  void WiFiSetup( void );
  boolean WiFiIsCONNECTED( void );
  void WiFiHandleClient( void );

#endif
