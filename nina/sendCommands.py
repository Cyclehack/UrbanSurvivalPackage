#!/usr/bin/env python

import serial

# This nasty tty variable is iffy
ser = serial.Serial('/dev/tty.test2-DevB')
ser.baudrate = 9600

ser.write('S')
