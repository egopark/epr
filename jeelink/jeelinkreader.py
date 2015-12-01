#!usr/bin/env python
import serial, sys
from datetime import datetime
ser = serial.Serial('devttyUSB0', 57600)

while 1:
  line = ser.readline()
  data = line.split()
  if len(data)>2:
    if ((data[0]=="OK") and (data[1]=="9")):
      print data
