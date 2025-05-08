#ifndef INTERNAL_DHT22_SENSOR_H
#define INTERNAL_DHT22_SENSOR_H

#include "DHT.h"

//Defining the pin on the pico to use for the DHT22 sensor
#define Internal_DHT22_PIN 8

//Setup fuinction to initalize the DHT22 sensor
void setup_Internal_DHT22();

//The data reading function that takes in references to two variables and 
//assign's it the value of temperature and humidity from the DHT22
void temp_and_humidity_Internal_read_DHT22(float &humi, float &tempF, bool farenheight);

#endif