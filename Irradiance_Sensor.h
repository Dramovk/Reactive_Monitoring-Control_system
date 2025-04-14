#ifndef IRRADIANCE_SENSOR_H
#define IRRADIANCE_SENSOR_H

#include "Arduino.h"

//The pin to read the voltage from the irradiance sensor
#define IRRADIANCE_PIN 28

//Setup function that changes the analog read resolution for the irradiance value
void irradiance_Setup();

//A function that measures the irradiance using an analog read on the irradiance pin 
void measure_Irradiance(float& irradiance);

#endif
