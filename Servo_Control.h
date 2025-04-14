#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

//The library to use servo functions
#include <Servo.h>

// The pin on the pico that changes the servo angle
#define SERVO_PIN 12

//The pin on the pico that reads a voltage level from the servo potentiometer
#define SERVO_CONTROL_PIN -1

//Function to setup the servo
void servo_Setup();

//A function to move the servo autonomusly
void autonomus_servo_control(int open_percentage);

//A function to move the servo based on a manual potentiometer control
void manual_servo_control(int servo_control_pin);

#endif