#!usr/bin/env python
import serial, sys, os
from datetime import datetime, timedelta
usbDevice = '/dev/ttyUSB0'

if os.path.exists(usbDevice):
  ser = serial.Serial(usbDevice, 57600)
  while 1:
    line = ser.readline()
    data = line.split()
    if len(data)>2:
      if ((data[0]=="OK") and (data[1]=="9")):
        sensor_node_address = data[2]
        battery = (int(data[3]) & 0x80) >> 7
        sensor_type = (int(data[3]) & 0x70) >> 4
        channel = (int(data[3]) & 0x0F)
        temperature = (int(data[4])*256+int(data[5])-1000)/10
        humidity = int(data[6]) & 0x7F
        if humidity == 106:
          humidity = ""
        bat_low = (int(data[6]) & 0x80) >> 7
        filename = "t_" +datetime.now().strftime("%y_%m_n") + str(sensor_node_address)+".log"
        if os.path.exists(filename):
          mode = 'a'
          last_modified = datetime.fromtimestamp(os.stat(filename).st_mtime)
          now = datetime.today()
          delay = timedelta (minutes = 15)
          writeCondition = ((now - last_modified) > delay)
        else:
          mode = 'w'
          writeCondition = True
        if writeCondition:
          f = open(filename, mode)
          f.write(str(datetime.now().strftime("%y-%m-%d %H:%M")) + " " + str(temperature) + " " + str(humidity) +"\r\n")
          f.close()
