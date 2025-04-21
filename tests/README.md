# Example Programs

[简体中文](README_ZH.md)  

In there, you can see some foundational example programs.

## LED_light.cpp

Using: LED light

Relevant code: src/LED

Function: After running the program, the small light starts to flash at fixed intervals. Press 0 to 9 to change the flashing interval of the small light, and press q to exit.

## HCSR04_Printer.cpp

Using: HCSR04 ultrasonic sensor

Relevant code: src/Ultrasonic

Function: After running the program, press enter. The sensor will start measuring and display the real-time distance on the screen. Press enter again to exit.

## LOGO.cpp
Using: N/A

Relevant code: src/Arknights

Function: Print the logo of the game "Arknights" and the artistic word name of Thermal-EX. This game is really fun!

## SG90_move.cpp
Using: SG90 servo with a range of 180 degrees, pwm

Relevant code: src/SG90

Function: After the program starts, the SG90 servo quickly returns to the 90-degree position and rotates to the corresponding Angle according to the numbers entered on the keyboard. Enter 999 to exit the program.

## Audio_greeting.cpp
Using: USB Speaker

Relevant code: src/AudioPlayer

Function: Play ` ThermalExVoice/Greeting. Wav `. Thermal-EX is greeting you.

## DistanceWaring.cpp
Using: HCSR04 ultrasonic sensor, LED small light, SG90 servo with a range of 180 degrees, pwm

Relevant code: src/LED，src/Ultrasonic，src/Keyboard，src/SG90

Function: Input "S" to start. After that, SG90 begins to rotate within a certain range, Thermal-EX starts to swing its head, and at the same time, the LED light flashes slowly. When the ultrasonic detection distance is less than the threshold, SG90 stops and the LED flashing frequency increases. Enter "Q" to exit.

## DistanceWaringSimple.cpp
Using: HCSR04 ultrasonic sensor, LED small light, SG90 servo with a range of 180 degrees, pwm

Relevant code: src/LED，src/Ultrasonic，src/SG90

Function: Press enter to start. After that, SG90 begins to rotate within a certain range, Thermal-EX starts to swing its head, and at the same time, the LED light flashes slowly. When the ultrasonic detection distance is less than the threshold, SG90 stops and the LED flashing frequency increases. Press enter to exit.