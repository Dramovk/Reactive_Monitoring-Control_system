#ifndef EXTERNAL_SHT30_SENSOR_H
#define EXTERNAL_SHT30_SENSOR_H

//Including relevant libraries to be used in the CPP file
#include <Arduino.h>
#include <SensirionI2cSht3x.h>
#include <Wire.h>

//PINS used for I2C on pico
// External_SHT30_PIN SDA - 0 / SCL - 1 

//A function to setup the SHT30 Sensor
void setup_External_SHT30();

//A function that reads and assigns the temperature and humidity values from the SHT30 sensor to two variables
void temp_and_humidity_External_read30(float &aHumidity, float &aTemperature, bool farenheight);


#endif