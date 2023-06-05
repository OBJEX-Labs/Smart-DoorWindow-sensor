***DOC TO BE COMPLETED!***

The documentation is not completed is will be edited in the coming days. Thanks!

Todo:
- [ ] Demo firmware for AWS IoT Core
- [ ] Demo firmware for Tuya
- [ ] Test OTA
- [ ] Measure the power consumption with oscilloscope + shunt resistor?
- [ ] Fix XOR footprint
- [ ] Fix reset button
- [ ] Fix battery socket pads - invert polarity

# Smart Door/Window sensor
The focus of this project is to prove how it is possible to drastically reduce the power consumption(in deep sleep/standby) of battery-powered smart devices by developing a customized power latch. Better design of smart devices would ensure a longer product life cycle.

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/docs/pcb.JPG)

## Power consumption

### Measurement range of PPK2
The current was measured with Nordic's power profiler kit , knowing that the current measured is less than the measurement range of this power profiler. I did several tests to verify the accuracy of the data. In any case the accuracy of the data, the consumption would be less than 200nA and this is a very good result considering that a similar device at a power consumption of 6-8uA.

### 1. Reed switch version
The consumption in deep sleep(POWER LATCH) is the same whether the magnet near the sensor or not.

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/Simulations%20%26%20Tests/deepsleep.png)

...in the coming days add more screenshots...

### 2. MAGNETIC SENSOR IC(S-5701) version
deepsleep: 300nA

...in the coming days add more screenshots...

## 3D Case

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/TOP.JPG)

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/Inside.JPG)

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/BatterySocket.JPG)

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/Magnet.JPG)
