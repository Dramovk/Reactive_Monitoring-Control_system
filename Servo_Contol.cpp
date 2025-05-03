//**********************************************//
//                 SERVO DEFINITIONS           //
//File to control the Servo and therefore the outlet orifice

#include "Servo_Control.h"

//Creating a servo instance
Servo outlet_orifice;

//A variable to see if the servo control pin has changed 
//AKA the potentiometer has been moved
int prev_servo_Voltage = 0;

//A function to setup the servo by attaching the instance to the defined servo pin
void servo_Setup(){
  outlet_orifice.attach(SERVO_PIN);
}

//A function to autonomuslky move the servo based on a percentage open used
void autonomus_servo_control(int open_percentage){
  //Unccoment Print statments when debugging/validating servo movements
  //Serial.print("open_percentage:   ");
  //Serial.println(open_percentage);
  //Assiging the open percentage to the avaialble range found experimentally from the 
  //vent openeing and the servo data sheet and 
  int angle=open_percentage*10+1100;
  //Moving the servo based on the openenign 1100 is fully open 2100 is fully closed
  outlet_orifice.writeMicroseconds(angle);//Between 1100-2100
}

//Function that takes in a percentage and opens the louvered vent that amount
void manual_servo_control(int servo_control_pin){
  //Reading the voltage level from the potentiometer 
  int read_Voltage_Value=analogRead(servo_control_pin);
  //Checking to see if the voltage level has changed indicating we need to move the servo arm
  if(read_Voltage_Value!= prev_servo_Voltage){
    //Storing the current voltage level to hold as a reference for the change
    prev_servo_Voltage=read_Voltage_Value;
    //Serial.println(read_Voltage_Value);
    //mapping the voltage to an open percentage of the servo
    int open_percentage = map(read_Voltage_Value, 20, 4050, 0, 100);
    //Serial.println(open_percentage);
    //Movng the servo in the same way as above but from the analog read out of the potentiometer.
    int angle=open_percentage*10+1100;
    outlet_orifice.writeMicroseconds(angle);
  }
}