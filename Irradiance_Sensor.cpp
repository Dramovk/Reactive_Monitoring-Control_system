//**********************************************//
//                 Irradiance DEFINITIONS           //
//File to read the Irradiance from the PYRONOMETER only

//Including the proper header file
#include "Irradiance_Sensor.h"

// Define the reference voltage and resolution for irradiance 
const float referenceVoltage = 3.3;
const float resolution = 4095;  // 12-bit resolution for the Pico's ADC adjusted to 12 bits

//Setting the maximums of the readings
const int max_voltage=2.5; //Settting the max voltage from he irradiance sensor
const int max_irradiance=1800; //setting he max irraidnace that should be read from the pyronometer

//A function to change the analog read resolution for the pico to get highest resolution of irradinace.
void irradiance_Setup(){
  //Setting the pico to analog read at its max resolution of 12 for the irradiance value
  analogReadResolution(12);
}

// Function to measure irradiance by converting voltage to irradiance
void measure_Irradiance(float& irradiance) {
  int rawValue = analogRead(IRRADIANCE_PIN);  // Read the raw ADC value (0-1023)
  float voltage = (rawValue / resolution) * referenceVoltage; 
  if (voltage < 0) {
    irradiance = 0;
  } else if (voltage > max_voltage) {
    irradiance = max_irradiance;
  } else {
    irradiance = (voltage / max_voltage) * max_irradiance;
  }
}
