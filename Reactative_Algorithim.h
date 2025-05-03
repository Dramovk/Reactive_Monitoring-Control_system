#ifndef REACTIVE_ALGORITHIM_H
#define REACTIVE_ALGORITHIM_H

//IUncluding the math library to use in the functions
#include <Math.h>
#include <Arduino.h>

//Function to calculate the EMC
void calculate_EMC(float tempF, float RH, float &returnEMC);

//Function to check the EMC based on temperature and Humidity
void Reactive_EMC_Algorithim(float temperatureF, float humidityRH, int & fan_speed, float &returnCurrentEMC);

//Function to run the reactive algorithm
//void reactive_Algorithim(int &fan_Speed, int &outlet_Opening, float external_Temp, float external_Humidity, float internal_Temp, float internal_Humidity, float target_temp);


#endif