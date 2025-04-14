//**********************************************//
//                 Fan DEFINITIONS           //
//File to control the fan and therefore the CFM in the dryer

//Including the proper header file
#include "Fan_Control.h"

//A variable to track if the voltage from the fan potentiometer has changed or not
int prev_fan_Voltage = 0;

//A function to setup the fan control pins
void Fan_setup() {
  //Setting the fan pin to be an output
  pinMode(FAN_PIN, OUTPUT);
  //initalizing the gate of the MOSFET to 0 so there is no floating voltage
  digitalWrite(FAN_PIN, LOW);
}

//Function to call to set the fan speed autonomusly
void autonomus_fan_control(int percentage){
  //Calculating the fan speed to be between 0 and 255 based on a percentage 0 to 100
  int fan_speed= percentage*2.55;
  //Writing the fan pin the specific speed
  analogWrite(FAN_PIN, fan_speed);
}

//A function to use a potentiometer to manually set the fan speed
void manual_fan_control(int fan_Pin){
  //Reading the voltage to the pin from the fan potentiometer
  int read_Voltage_Value=analogRead(fan_Pin);
  //Checking to see if the potentiometer has been chnaged or not
  if(read_Voltage_Value!= prev_fan_Voltage){
    //Tracking the previous voltage level to know if it has changed or not
    prev_fan_Voltage=read_Voltage_Value;
    //Serial.println(read_Voltage_Value);
    //Making the potentiometer voltage be a value for fan speed percentage between 0 and 100 
    //subject to change based on fan speed threshold
    int fan_percentage = map(read_Voltage_Value, 35, 975, 0, 100);
    //Serial.println(fan_percentage);
    //Setting the fan speed in a similar fashion to the autonomus control.
    int fan_speed= fan_percentage*2.55;
    analogWrite(FAN_PIN, fan_speed);
  }
}