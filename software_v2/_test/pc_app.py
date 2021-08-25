#!/usr/bin/env python
import time
import serial
import numpy as np
import matplotlib.pyplot as plt

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
	port='/dev/ttyACM0',
	baudrate=115200
)

plt.ion()
plt.axis([0, 10, 0, 10000])
fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
# fig, ax = plt.subplots()
max_ = 10000
r_ = np.arange(0, max_, 0.01)
theta_ = 2 * np.pi * r_/ max_
line1, = ax.plot(theta_, r_, '.')

r = []
theta = []
data = ''
cnt = 0
while True:
	s = ser.read(1)
	if (s == '\n') or (s == '\r'):
		try:
			data_ = data.split(' ')
			distance = float(data_[0].strip())
			angle = float(data_[1].strip())
			quality = int(data_[2].strip())
			if quality >= 0:
				# print(angle, distance, quality)
				if distance > 0: # 1000:
					r.append(distance)
					theta.append(angle * np.pi/180.0)
					if len(r) > 500:
						r.pop(0)
					if len(theta) > 500:
						theta.pop(0)
				if cnt%600 == 0:
					r_ = np.asarray(r)
					theta_ = np.asarray(theta)
					# plt.scatter(theta_, r_)
					line1.set_xdata(theta_)
					line1.set_ydata(r_)
					# plt.pause(0.05)
					fig.canvas.draw()
					fig.canvas.flush_events()
				cnt += 1
		except:
			data = ''
	else:
		data += s

