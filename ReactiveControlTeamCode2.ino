//All inclusions of necessary Header files and libraries
#include "Arduino.h"
#include "Internal_DHT22_Sensor.h"
#include "Servo_Control.h"
#include "SD_Card.h"
#include "Fan_Control.h"
#include "External_SHT30_Sensor.h"
#include "Irradiance_Sensor.h"
#include "LCD.h"
#include "Reactative_Algorithim.h"
#include "Digital_Potentiometer.h"

//Test
//ALL COMBINED CODE FOR TH SOLAR CROP DRYER

/*PLUG IN SD CARD PINS OR CODE WILL NOT RUN BECAUSE OF THE SD CARD SETUP FUNCTION*/


/* PINS NOT USED IN MAIN FUCTION BUT FOR FUNCTIONALITY
 External_SHT30_PIN SDA - 0 / SCL - 1
 FAN_PIN 13
 SERVO_PIN 12
 DHT22_PIN 8
 irradiance_pin 28
***********************************
LCD SCREEN PINS:
 TFT_CS     5   // Chip Select (CS)
 TFT_DC     6   // Data Command (DC)
 TFT_MOSI   3   // SPI MOSI (DIN)
 TFT_CLK    2   // SPI Clock (CLK)
 TFT_RST    4   // Reset (RST)

//SD card attached to SPI bus as follows:
  MOSI - pin 19
  MISO - pin 16
  CLK - pin 18
  CS - pin 17

//USER INPUT PINS
  POTENTIOMETER_PIN_1  27
  POTENTIOMETER_PIN_2  26 
  BUTTON_PIN  21
 */


//USER INPUT PINS
//Setting the pins for the potentiometers and button
#define POTENTIOMETER_PIN_1  27
#define POTENTIOMETER_PIN_2  26 
#define BUTTON_PIN  21

//Variables to hold the temperature and humidity etc
float irradiance_value = -1, external_Temp=-1, external_Humidity=-1, internal_Temp=-1, internal_Humidity=-1, internal_TargetTemp=-1, internal_EMC=-1;
int fan_Speed= 83, outlet_Opening=20;

int timer =0; // central "clock" in which we determine how often events happen
int state = -7; // determines which "state" or mode we are in, determines which "window" is displayed on the LCD
int EMC_calculation_interval= 5; // Time at which the internal EMC is calculated in minutes
bool fahrenheit=true; //Wether to read temperature in fahrenheit or celcius if true fahrenheit if false celcius

//variables to keep track of the timing of recent interrupts and button opetations
unsigned long button_time = 0;  
unsigned long last_button_time = 0;
int buttonState = 0;  // Current button state
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;  // The last time the button was toggled
unsigned long debounceDelay = 50;  // The debounce time; increase if the button is noisy

// Variables to count time passed for other operations
int time_1 = 0;
int time_2 = 0;
bool interval = false;
int potenValue = 0; // potentiometer value

//time variables for data logging
int dLog_time1= 0;
int dLog_time2= 0;
int data_log_interval= 1; // time at which data is logged on the SD card 
bool data_log_flag = false;

//Potentiometer variable and date and time values to set up date and time.
int potentiometer_variable=0;
int interem_value=0;
int year_value=2025;
int month_value=1;
int day_value=1;
int hour_value=1;
int minute_value=1;

//Count and Boolean Variables for automated testing
int fanCount=0;
int dryerState=0;
int outletCount=0;
bool outletSweep=true;
bool fanSweep=false;

void isr(){ // this debounces and checks for button selection.
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
      state = state+1;
      if(state == 3){
        state = 0;
      }
      last_button_time = button_time;
  }
}

void setup() {
  //Starting the serial monitor at a baud rate of 9600
  Serial.begin(9600);
  //*******************************************
  // setup for the SERVO
  servo_Setup();
  //*******************************************
  //Stating the read resolution for the irradiance sensor
  irradiance_Setup();
  //*******************************************
  // intializing the SHT30 and DHT22 sensor
  setup_External_SHT30();
  setup_Internal_DHT22();//Starting the DHT22
  //*******************************************
  //LCD SETUP FUNCTION
  LCDStart();
  //*******************************************
  //Setting up the fan speed function
  digital_Potentiometer_Setup();
  //Initalizing fan speed to 0
  set_Motor_Speed(70);
  //
  //*******************************************
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  attachInterrupt(BUTTON_PIN, isr, FALLING); // creates interrupt
}

void autonomusly_Set_Actuators(int fan, int outlet){ // this sets the actuators to whatever values we want.
  //Changing the fan speed and Outlet size based on values passed in
  set_Motor_Speed(fan);
  autonomus_servo_control(outlet);
}

void logData()
{
  //*********Updating the SD Card with the data*************
  data_Log(external_Humidity, external_Temp, internal_Humidity, internal_Temp, irradiance_value, fan_Speed, outlet_Opening, internal_EMC);
}

void update_LCD_Variables(){ // gathers and logs and updates LCD with data
  //*********Reading the DHT22 and SHT30 sensors*****************
  temp_and_humidity_Internal_read_DHT22(internal_Humidity, internal_Temp, fahrenheit);
  temp_and_humidity_External_read30(external_Humidity, external_Temp, fahrenheit);
  //*********Reading the Irradiance sensor*************
  measure_Irradiance(irradiance_value);
  //********* Update the LCD and current file's globals with new data
  UpdateLCDValues(fan_Speed, outlet_Opening, external_Temp, internal_Temp, external_Humidity, internal_Humidity, irradiance_value, EMC_calculation_interval, data_log_interval);
}

//A function that reads the value of potentiometer 1 to use for setting year, month, and day
void read_Potentiometer_1(int &potentiometer_value)
{
  potentiometer_value = analogRead(POTENTIOMETER_PIN_1);
      if(potentiometer_value <20)
        potentiometer_value = 20;
      if(potentiometer_value>4050)
        potentiometer_value = 4050;
}

void loop() {
  //time variables for intervals
  time_1 = millis();
  dLog_time1=millis();
  //Logging data based on the interval passed set by the user. This is defaulted to 1 second.
  if(dLog_time1 - dLog_time2 > (data_log_interval * 60 * 1000))
  {
    dLog_time2 = dLog_time1;
    data_log_flag=true;
  }
  else
  {
    data_log_flag = false;
  }

  //updating the LCD every second to make it easier for the user to see.
  if (time_1 - time_2 > 1000) 
  {             
    time_2 = time_1;
    interval = true;
    //Print stuff
    Serial.print("Case: ");
    Serial.println(state);
    Serial.print("ButtonPress: ");
    Serial.println(digitalRead(BUTTON_PIN));
    Serial.print("Poten 1: ");
    Serial.println(analogRead(POTENTIOMETER_PIN_1));
    Serial.print("Poten 2: ");
    Serial.println(analogRead(POTENTIOMETER_PIN_2));
  }
  else{
    interval = false;
  }
  switch(state)
  {
      /*
        Notice that the interrupt resets the case value to 0, not -3.
        So, the states -7 to -1 will only "run once", and are reset 
        only when the program is re run. 
        Example: User starts it, case =-7, user sets year, button press
        goes to -6, user sets month, etc... now case is equal to 2, 
        button press resets to 0, so that cases -7 to -1 never get 
        revisited. 
        */
    
    case -7:
    {
      // this is the set year 
      //Reading the potentiometer value from potentiometer 1
      read_Potentiometer_1(potentiometer_variable);
      year_value = map(potentiometer_variable,0,4050,2025,2030);
      if(interval)
      { 
        Intro_Set(1, year_value, month_value, day_value, hour_value, minute_value, 0);// sets GUI page
        setYear(year_value);
      }
      //setGUI(#some number corresponding to the year GUI);
      break;
    }
    case -6:
    {
      // this is the set month
      // the potentiometer value from potentiometer 1
      read_Potentiometer_1(potentiometer_variable);
      month_value = map(potentiometer_variable,0,4050,1,12);
      if(interval)
      {
        Intro_Set(2, year_value, month_value, day_value, hour_value, minute_value, 0); // sets GUI page
        setMonth(month_value);
      }
      break;
    }
    case -5: 
    {
      // this is the set day
      // the potentiometer value from potentiometer 1
      read_Potentiometer_1(potentiometer_variable);
      day_value = map(potentiometer_variable,20,4050,1,31);
      if(interval)
      {
        Intro_Set(3, year_value, month_value, day_value, hour_value, minute_value, 0); // sets GUI page
        setDay(day_value);
      }
      break;
    }
    case -4: 
    {
      // this is the set hour
      // the potentiometer value from potentiometer 1
      read_Potentiometer_1(potentiometer_variable);
      hour_value = map(potentiometer_variable,20,4050,0,23);
      if(interval)
      {
        Intro_Set(4, year_value, month_value, day_value, hour_value, minute_value, 0); // sets GUI page
        setHour(hour_value);
      }
      break;
    }
    case -3: 
    {
      // this is the set minute
      // the potentiometer value from potentiometer 1
      read_Potentiometer_1(potentiometer_variable);
      minute_value = map(potentiometer_variable,20,4050,0,59);
      if(interval)
      {
        Intro_Set(5, year_value, month_value, day_value, hour_value, minute_value, 0); // sets GUI page
        setMinute(minute_value);
      }
      break;
    }
    case -2:
    {
      //*******************************************
      //Set wether system is in Celcius or Farenheihght
      read_Potentiometer_1(potentiometer_variable);
      if(interval)
      {
        Intro_Set(6, year_value, month_value, day_value, hour_value, minute_value, potentiometer_variable); // sets GUI page
        if(potentiometer_variable > 2000)
        {
          fahrenheit = false; //making the fahrenheit boolean variable false because we are in celcius
        }
        else
        {
          fahrenheit = true; //making the fahrenheit boolean variable true because we are in fahrenheit
        }
      }
      //*******************************************
      break;
    }
    case -1:
    {
      //*******************************************
      //Setup for the SD CARD in order to data log
      //Starting the SD card after date has been set by user
      SD_setup(fahrenheit);
      //*******************************************
      state=0; // progressign the state to the next one
      break;
    }
    case 0:
    {
      //Commented out EMC Reactive algorithim call
      Reactive_EMC_Algorithim(internal_Temp, internal_Humidity, fan_Speed, internal_EMC, EMC_calculation_interval);
      //Checking to see if the data log inetval has triggered
      if(data_log_flag){
        logData(); // logs data
      }
      if(interval)
      {
        update_LCD_Variables();
        Serial.println("in auto");
        automaticGUI(); // runs the automaticGI window
        autonomusly_Set_Actuators(fan_Speed, outlet_Opening);
      }
      
    break;
    }
    case 1: // manuel mode - only in this state do analog reads work 4 poteniometer
    {
      // manuel viewing (you can see the values that you have set, but you can't set them)
      //Serial.println("Manual");
      int fan_value =analogRead(POTENTIOMETER_PIN_1); // from poteniometer pin 
      int servo_value =analogRead(POTENTIOMETER_PIN_2); // from poteniometer pin 
      if(fan_value <20)
        fan_value = 20;
      if(fan_value>4050)
        fan_value = 4050;
      if(servo_value<20)
        servo_value =20;
      if(servo_value>4050)
        servo_value =4050;
      fan_Speed = map(fan_value, 20, 4050, 0, 100);  // To percentage 
      outlet_Opening = map(servo_value, 20, 4050, 0, 100);  // To percentage              
      //Checking to see if the data log inetval has triggered
      if(data_log_flag){
        logData(); // logs data
      }
      //Checking to see if the interval has elapsed
      if(interval){ // 1 second interval
        update_LCD_Variables();
        manualGUI(); // runs the automaticGUI window
        autonomusly_Set_Actuators(fan_Speed, outlet_Opening);
      }
      break;
    }
    case 2:
    {
      int EMC_value =analogRead(POTENTIOMETER_PIN_1); // from poteniometer pin 
      int dLog_value =analogRead(POTENTIOMETER_PIN_2); // from poteniometer pin 
      EMC_calculation_interval = map(EMC_value, 20, 4050, 1, 10);
      data_log_interval = map(dLog_value, 20, 4050, 1, 10);
      //Checking to see if the data log inetval has triggered
      if(data_log_flag){
        logData(); // logs data
      }
      //Checking to see if the interval has elapsed
      if(interval){ // 1 second interval
        update_LCD_Variables();
        adjustParametersGUI(); // runs the adjust Parameters GUI window
      }
      break;
    }
  }
}
