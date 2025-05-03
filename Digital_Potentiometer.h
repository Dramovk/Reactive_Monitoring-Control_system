#ifndef DIGITAL_POTENTIOMETER_H
#define DIGITAL_POTENTIOMETER_H

#include <Arduino.h>

// === GPIO Pins (change if needed) ===
#define DPOT_INC_PIN 13  // GPIO2 on RP2040
#define DPOT_UD_PIN  14  // GPIO3
#define DPOT_CS_PIN  15  // GPIO4

//fucntion to set up the digital potentiometer
void digital_Potentiometer_Setup();

//RANG OF MOTOR SPEED is 70 to 100 70 is off
//Function to set the motor speed by changing the digital potentiometer position
void set_Motor_Speed(int percent);

//function to pulse the increment pin
void pulseInc();

#endif