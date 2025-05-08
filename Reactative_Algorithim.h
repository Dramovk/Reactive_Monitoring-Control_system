#ifndef REACTIVE_ALGORITHIM_H
#define REACTIVE_ALGORITHIM_H

//IUncluding the math library to use in the functions
#include <Math.h>
#include <Arduino.h>

//Function to calculate the EMC
void calculate_EMC(float tempF, float RH, float &returnEMC);

//Function to check the EMC based on temperature and Humidity
void Reactive_EMC_Algorithim(float temperatureF, float humidityRH, int & fan_speed, float &returnCurrentEMC, int EMC_interval);

#endif