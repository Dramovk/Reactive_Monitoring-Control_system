//Including corresponding .h file
#include "Reactative_Algorithim.h"

// --- Constants ---
const unsigned long EMC_INTERVAL = 5 * 60 * 1000; // 5 minutes in ms

// --- State Variables ---
unsigned long emcPreviousMillis = 0;
bool emcFirstRun = true;
float emcPreviousValue = 0.0;
float currentEMC = 0.0;
int direction = -1;

// --- Calculate EMC --- using temperature and humidity
void calculate_EMC(float tempF, float RH, float &returnEMC) {
  //Constants to use in the EMC equation
  float C = 30.205;
  float E = 0.33872;
  float F = 0.05897;

  //Calculating EMC with given temperature and humidity
  float log_RH = log(RH / 100.0);
  float tempC = (tempF - 32.0) * (5.0 / 9.0);
  float temp_plusC = -(tempC + C);
  float multiplyLnRh = temp_plusC * log_RH;

  

  //Using last constants to get the EMC value
  float multiplyByF = -log(multiplyLnRh) * F;
  float EMCd = (multiplyByF + E) * 100.0;
  float EMCw = (100.0 * EMCd) / (100.0 + EMCd);

  //REutrning the EMC value
  returnEMC = EMCw;
  if (multiplyLnRh <= 0) returnEMC = -1; // Invalid domain for log
  //void function so return nothing
  return;
}

// --- Control Loop Function ---
void Reactive_EMC_Algorithim(float temperatureF, float humidityRH, int &fan_speed, float &returnCurrentEMC) {
  unsigned long currentMillis = millis();//Getting current time

  if (currentMillis - emcPreviousMillis >= EMC_INTERVAL || emcFirstRun) {// CHecking to see if the interval of 5 minutes has elapsed or its the first run
    emcPreviousMillis = currentMillis;

    //getting th current EMC value
    calculate_EMC(temperatureF, humidityRH, currentEMC);

    if (currentEMC < 0) {
      Serial.println("Invalid EMC calculation (log domain error).");// checking to see if the log function returned a bad value
      return;
    }

    // if its not the first run compare the EMC and change fan speed either up or down based on if the EMC helped or not
    if (!emcFirstRun) {
      //Checking to see if EMC went up down or stayed the same
      //IF EMC GOES UP
      if (currentEMC > emcPreviousValue) {
        Serial.println("EMC went UP.");
        // TODO: Add logic for when EMC goes UP
        //if fan speed was just increased and it caused EMC to increase then switch and decrease fan speed
        if (direction > 0)
        {
          fan_speed = fan_speed - 1;
          direction = -1;
        }
        //IF fan speed was previously decreaseed and it caused EMC to increase then switch and Increase fan speed
        else if (direction < 0){
          fan_speed = fan_speed + 1;
          direction = 1;
        }
        //IF EMC GOES DOWN
      } else if (currentEMC < emcPreviousValue) {
        Serial.println("EMC went DOWN.");
        // TODO: Add logic for when EMC goes DOWN
        // IF fan speed was decreased an we caused EMC to go down keep it decreasing
        if(direction < 0)
        {
          fan_speed = fan_speed -1;
          direction = -1;
        }
        // IF fan speed was increased and it caused EMC to go down keep it increasing
        else if(direction > 0)
        {
          fan_speed = fan_speed + 1;
          direction = 1;
        }

       //IF EMC DOES NOT CHANGE
      } else {
        Serial.println("EMC stayed the same.");
        //Using the previous direction and doing bigger change if the EMC is not changing
        // If fan speed was decereased and there was no change in EMC decrease fan speed more
        if(direction < -1)
        {
          fan_speed = fan_speed - 3;
          direction = -1;
        }
        // IF  fan speed was increased and there was no change in EMC increase fan speed more
        else if (direction > 0)
        {
          fan_speed = fan_speed + 3;
          direction = 1;
        }
      }
      //Putting in the bounds of fan speed the minimum being 83 and max being 100
      if (fan_speed <83)
      {
        fan_speed = 83;
      }
      if(fan_speed >100)
      {
        fan_speed = 100;
      }
    }

    emcPreviousValue = currentEMC;
    returnCurrentEMC = currentEMC;
    emcFirstRun = false;

    //Printing the EMC value to the terminal
    Serial.print("Current EMC: ");
    Serial.println(currentEMC);
  }
  return;
}

/*
//a  reactive algorithm that sets fan speed and outlet openening based on the internal temprature compared to the target temperature for a give internal humidity.
void reactive_Algorithim(int &fan_Speed, int &outlet_Opening, float external_Temp, float external_Humidity, float internal_Temp, float internal_Humidity, float target_temp){
  float temp_Diff= internal_Temp-target_temp;// creating a differential variable to use as a comparison from our internal temperature to the target temperature.
   //setting edge cases of humidity and temperature.
  if(external_Humidity>85){
    // It is too humid for us to ever reach the desired EMC and it is probably raining?
    fan_Speed = 75;// run fan as slow as possible to keep it from bring super moist air in
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
    fan_Speed = 95;//run fan at mid speed
    outlet_Opening=20; //open vent half  way
  }
  else if (temp_Diff > 3)//if the itnernal temperature is hotter than our taget temp plus 3 degrees
  {
    fan_Speed = 88;//run fan at mid speed
    outlet_Opening=20; //open half way
  }
  else if (temp_Diff > 1)//if the itnernal temperature is hotter than our taget temp under 3 degrees but hotter
  {
    fan_Speed = 83;//run fan at min speed
    outlet_Opening=40; //close vent all the way try to keep fan here
  }
  else if (temp_Diff < -10)//if the itnernal temperature is colder than our taget temp - 10 degrees
  {
    fan_Speed = 83;//run fan at min speed
    outlet_Opening=40; //close vent all the way to let air warm up
  }
  else if (temp_Diff < -5)//if the itnernal temperature is colder than our taget temp by 5 degrees
  {
    fan_Speed = 88;//run fan at mid speed
    outlet_Opening=20; //open vent half  way
  }
  else if (temp_Diff < -3)//if the itnernal temperature is colder than our taget temp by 3 degrees
  {
    fan_Speed = 95;//run fan at mid speed
    outlet_Opening=20; //open half way
  }
  else if (temp_Diff < 1)//if the itnernal temperature is colder than our taget temp but within 3 degrees
  {
    fan_Speed = 83;//run fan at min speed
    outlet_Opening=40; //close vent all the way try to keep dryer in this state
  }
  else// base case
  {
    fan_Speed = 83;//run fan at min speed
    outlet_Opening=0; //close vent all the way try to keep dryer in this state
  }
}*/