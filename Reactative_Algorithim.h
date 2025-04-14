#ifndef REACTIVE_ALGORITHIM_H
#define REACTIVE_ALGORITHIM_H

//IUncluding the math library to use in the functions
#include <Math.h>

//Function to get the target temerature
void calculate_Target_Temp(float &target_temp, float internal_Humidity);

//Function to run the reactive algorithm
void reactive_Algorithim(int &fan_Speed, int &outlet_Opening, float external_Temp, float external_Humidity, float internal_Temp, float internal_Humidity, float target_temp);


#endif