//Including corresponding .h file
#include "Reactative_Algorithim.h"

//An array holding the target values based on Relative humidity
float target_TempValues[19] = { -3.79, 1.8, 6.97, 12.22, 17.78, 23.86, 30.65, 38.38, 47.34, 57.93, 70.74, 86.6, 106.84, 133.49, 171.12, 227.08, 320.13, 505.93, 1062.81};  // Row 1

//Function to calculate the target temperature given the humidity in ranges of 5. 
void calculate_Target_Temp(float &target_temp, float internal_Humidity){
  int indexRH = round(internal_Humidity/ 5.0)-1; //calculating the index of the target value based on the internal humidity
  target_temp = target_TempValues[indexRH]; // getting the specific target temperature value
}

//a  reactive algorithm that sets fan speed and outlet openening based on the internal temprature compared to the target temperature for a give internal humidity.
void reactive_Algorithim(int &fan_Speed, int &outlet_Opening, float external_Temp, float external_Humidity, float internal_Temp, float internal_Humidity, float target_temp){
  float temp_Diff= internal_Temp-target_temp;// creating a differential variable to use as a comparison from our internal temperature to the target temperature.
   //setting edge cases of humidity and temperature.
  if(external_Humidity>85){
    // It is too humid for us to ever reach the desired EMC and it is probably raining?
    fan_Speed = 30;// run fan as slow as possible to keep it from bring super moist air in
    outlet_Opening = 40;//close vent all the way to keep air in
  }
  else if(internal_Temp>190){
    //It is too hot inside, the corn may start to get damaged
    fan_Speed = 100;// turn fan on full speed to bring new cold air in.
    outlet_Opening = 0;// open vent all the way
  }
  else if (temp_Diff >10)//if the itnernal temperature is hotter than our taget temp plus 10 degrees
  {
    fan_Speed = 100;//run fan at full speed
    outlet_Opening=0; //open vent all the way
  }
  else if (temp_Diff > 5)//if the itnernal temperature is hotter than our taget temp plus 5 degrees
  {
    fan_Speed = 80;//run fan at mid speed
    outlet_Opening=20; //open vent half  way
  }
  else if (temp_Diff > 3)//if the itnernal temperature is hotter than our taget temp plus 3 degrees
  {
    fan_Speed = 70;//run fan at mid speed
    outlet_Opening=20; //open half way
  }
  else if (temp_Diff > 1)//if the itnernal temperature is hotter than our taget temp under 3 degrees but hotter
  {
    fan_Speed = 50;//run fan at min speed
    outlet_Opening=40; //close vent all the way try to keep fan here
  }
  else if (temp_Diff < -10)//if the itnernal temperature is colder than our taget temp - 10 degrees
  {
    fan_Speed = 50;//run fan at min speed
    outlet_Opening=40; //close vent all the way to let air warm up
  }
  else if (temp_Diff < -5)//if the itnernal temperature is colder than our taget temp by 5 degrees
  {
    fan_Speed = 70;//run fan at mid speed
    outlet_Opening=20; //open vent half  way
  }
  else if (temp_Diff < -3)//if the itnernal temperature is colder than our taget temp by 3 degrees
  {
    fan_Speed = 80;//run fan at mid speed
    outlet_Opening=20; //open half way
  }
  else if (temp_Diff < 1)//if the itnernal temperature is colder than our taget temp but within 3 degrees
  {
    fan_Speed = 50;//run fan at min speed
    outlet_Opening=40; //close vent all the way try to keep dryer in this state
  }
  else// base case
  {
    fan_Speed = 50;//run fan at min speed
    outlet_Opening=0; //close vent all the way try to keep dryer in this state
  }
}