# Smart Door/Window sensor
The focus of this project is to prove how it is possible to drastically reduce the power consumption(in deep sleep/standby) of battery-powered smart devices by developing a customized power latch. Better design of smart devices would ensure a longer product life cycle.

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/docs/pcb.JPG)

## Power consumption

### Measurement range of PPK2
The current was measured with Nordic's power profiler kit , knowing that the current measured is less than the measurement range of this power profiler. I did several tests to verify the accuracy of the data. In any case the accuracy of the data, the consumption would be less than 200nA and this is a very good result considering that a similar device at a power consumption of 6-8uA.

### 1. Reed switch version
The consumption in deep sleep(POWER LATCH) is the same whether the magnet near the sensor or not.

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/Simulations%20%26%20Tests/deepsleep.png)

### 2. MAGNETIC SENSOR IC(S-5701) version
deepsleep: 300nA

## 3D Case

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/TOP.JPG)

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/Inside.JPG)

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/BatterySocket.JPG)

![image](https://github.com/salvatoreraccardi/Smart-DoorWindow-sensor/blob/main/3D/Magnet.JPG)
