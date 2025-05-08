//**********************************************//
//                 DHT22 DEFINITIONS           //
//File to read values from the dht22 and therefore the internal temperature and humidity

#include "Internal_DHT22_Sensor.h"

//Initalizing the internal dht22 sensor
DHT Internal_dht22(Internal_DHT22_PIN, DHT22);

//Just starting the instance of the DHT22 sensor in the setup function
void setup_Internal_DHT22(){
  Internal_dht22.begin();
}

//A function to get the temperature and humidity data from the dht22 Sensor
void temp_and_humidity_Internal_read_DHT22(float &humi, float &tempF, bool farenheight){
  //Reading humiditiy
  humi = Internal_dht22.readHumidity();

 

  if(farenheight){
    //READING TEMPERATURE IN FARENHEIGHT
    //reading temperature as farenhieght by passing in true if needed in celcius un comment line above
    tempF= Internal_dht22.readTemperature(true);
  }
  else{
    //READING TEMPERATURE IN CELCUIS
    tempF= Internal_dht22.readTemperature(false);
  }

  //Checking to see if the reads fail only unccoment when debugging a DHT22 sensor
  // if (isnan(humi) || isnan(tempF)){
  //   Serial.println("Failed to read from DHT22 Sensor!");
  // }
  // else {
  //   Serial.println("DHT22 # Humidity:  ");
  //   Serial.print(humi);
  //   Serial.print("%");
  //   Serial.print("    |   ");
  //   Serial.print("Temperature:  ");
  //   Serial.print(tempF);
  //   Serial.print("Farenheight");
  //   } 
  return;
}