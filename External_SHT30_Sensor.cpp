//**********************************************//
//                 SHT30 DEFINITIONS           //
//File to read the temperature and Humidity from the SHT30 sensor and therefore the external Temperature and Humidity.

//Including the proper header file
#include "External_SHT30_Sensor.h"

//A variable to start the instance of the SHT30 sensor
SensirionI2cSht3x External_sensor;

//Variables to be used if there are error messages from the sensor
static char errorMessage[64];
static int16_t error;

//A function to setup the SHT30
void setup_External_SHT30() {
  //Setting the specific SCL and SDA pins for the sensor
  Wire.setSDA(0);  // Set SDA pin
  Wire.setSCL(1);  // Set SCL pin
  //Starting I2C communication
  Wire.begin();    // Start I²C

  //Starting the SHT30 Sensor
  External_sensor.begin(Wire, SHT30_I2C_ADDR_44);

  //Stopping the measurement
  External_sensor.stopMeasurement();
  delay(1);
  //Restarting the measurment to ensure the sensor is working properly
  External_sensor.softReset();
  delay(100);
  //Creating a register to hold the status of the SHT30
  uint16_t aStatusRegister = 0u;
  //Reading the status of the SHT30 sensor
  error = External_sensor.readStatusRegister(aStatusRegister);
  //Checking to see if there where any errors in the initalization of the sensor. 
  //If so printing them out on the serial monitor
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute readStatusRegister(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    return;
  }
  //Serial.print("aStatusRegister: ");
  //Serial.print(aStatusRegister);
  //Serial.println();
  //Starting a periodic measurment on the SHT30
  error = External_sensor.startPeriodicMeasurement(REPEATABILITY_MEDIUM,
                                          MPS_ONE_PER_SECOND);
  //Checking to see if there where any errors in starting the periodic measurment. 
  //If so printing them out on the serial monitor
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute startPeriodicMeasurement(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    return;
  }
}

//A function to read and update the values of the humidity and temperature from the SHT30
void temp_and_humidity_External_read30(float &aHumidity, float &aTemperature, bool farenheight){
  //Reading the temperature and humidity from the sensor while checking to see if there was an error
  error = External_sensor.blockingReadMeasurement(aTemperature, aHumidity);
  //Checking to see if there where any errors during the reading of the sensor. 
  //If so printing them out on the serial monitor
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute blockingReadMeasurement(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    return;
  }
  //Changing the temperature from celcuis to farenheight.
  //converting to farenheight if true
  if(farenheight){
    aTemperature= aTemperature * 9/5+32;
  }

}