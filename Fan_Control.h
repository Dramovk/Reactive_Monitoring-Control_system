#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include "Arduino.h"

//Assiging the specific pin for the Manual control to analog read the specific pico pin
#define Fan_CONTROL_PIN -1

//Defining the fan pin to contol the speed of the fan.
#define FAN_PIN 13

//A fuinction to set up the fan
void Fan_setup();

//A function so that the program can autonomusly control the fan
void autonomus_fan_control(int percentage);

//A function that allows for manual fan control
void manual_fan_control(int fan_Pin);

#endif