#!usr/bin/env python
import serial, sys, os
from datetime import datetime, timedelta

ser = serial.Serial('/dev/ttyUSB0', 57600)

while 1:
  line = ser.readline()
  data = line.split()
  if len(data)>2:
    if ((data[0]=="OK") and (data[1]=="9")):
      sensor_node_address = data[2]
      battery = (int(data[3]) & 0x80) >> 7
      sensor_type = (int(data[3]) & 0x70) >> 4
      channel = (int(data[3]) & 0x0F)
      temperature = int(data[4])*256+int(data[5])-1000
      humidity = int(data[6]) & 0x7F
      bat_low = (int(data[6]) & 0x80) >> 7
      filename = "t_h_"+ str(sensor_node_address)+".log"
      last_modified = datetime.fromtimestamp(os.stat(filename).st_mtime)
      now = datetime.today()
      delay = timedelta (minutes = 15)
      if now - last_modified > delay:
        f = open(filename, 'a')
        f.write(str(datetime.now()) + " " + str(temperature) + " " + str(humidity) +"\r\n")
        f.close()
