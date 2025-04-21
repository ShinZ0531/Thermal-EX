# 示例程序

这里提供了几个基础的示例程序。

## LED_light.cpp

使用到的组件：LED小灯

使用到的源码：src/LED，src/Arknights

功能：运行程序后，小灯开始以固定间隔闪烁，按下0-9可以改变小灯闪烁的间隔，按下q退出。

## HCSR04_Printer.cpp

使用到的组件：HCSR04超声波传感器

使用到的源码：src/Ultrasonic

功能：运行程序后，按下enter，传感器开始测量，并把实时距离显示在屏幕上，再次按下enter退出。

## LOGO.cpp

使用到的组件：无

使用到的源码：src/Arknights

功能：打印游戏《明日方舟》的logo和Thermal-EX的艺术字名字。这游戏真的很好玩！

## SG90_move.cpp

使用到的组件：范围为180度的SG90舵机，pwm

使用到的源码：src/SG90

功能：程序启动后，SG90舵机快速回到90度的位置，根据键盘输入的数字，旋转至对应角度。输入999退出程序。

## Audio_greeting.cpp

使用到的组件：USB音响

使用到的源码：src/AudioPlayer

功能：播放`ThermalExVoice/Greeting.wav`。Thermal-EX在跟你打招呼。

## DistanceWaring.cpp

使用到的组件：HCSR04超声波传感器，LED小灯，范围为180度的SG90舵机，pwm

使用到的源码：src/LED，src/Ultrasonic，src/Keyboard，src/SG90

功能：输入S启动，之后SG90开始在一定范围内旋转，Thermal-EX开始摆头，同时LED灯慢速闪烁。当超声波检测到距离小于阈值时，SG90停止，LED闪烁频率加快。输入Q退出。


## DistanceWaringSimple.cpp

使用到的组件：HCSR04超声波传感器，LED小灯，范围为180度的SG90舵机，pwm

使用到的源码：src/LED，src/Ultrasonic，src/SG90

功能：按下enter启动，之后SG90开始在一定范围内旋转，Thermal-EX开始摆头，同时LED灯慢速闪烁。当超声波检测到距离小于阈值时，SG90停止，LED闪烁频率加快。按下enter退出。