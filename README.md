# Maze Rover v1.0
The software in this project was used to create a maze-solving rover using a Rover 5 robot platform, an Atmel ATMega328 chip, and a QTR line sensor. The software is written in C, and can be compiled using the avr-gcc compiler.

## Compatible Hardware
Required Parts:
* Polulu QTR-8RC Reflectance Sensor Array
* Rover 5 robotics platform
* Atmel ATMega328 microcontroller
* LD33V 3.3V voltage regulator
* 2 x H-Bridge motor drivers
* 10uF electrolytic capacitor

Data Connections:

* QTR-8RC - PD0-PD1 (left sensors), PD7-PD8 (right sensors)
* Motor Drivers - PC3-PC4 (right motors), PC5-PC6 (left motors)

Logic Board Specifications:

* 9v (6 x AA @ 1.5v) battery pack
* MCU VCC is 3.3v *regulated*
* H-Bridge VIN is 9v *unregulated*
* PSU is an LD33V with a 10uF capacitor between VCC and GND

## Authors
Zachary Power: [@zachpwr](http://www.github.com/zachpwr) |
Zachary Maniatis: [@zmaniatis](http://www.github.com/zmaniatis)
