//**********************************************//
//                 SD Card DEFINITIONS           //
//File to write to a file on the Mirco SD Card Module

//Including the header file for the SD Card
#include "SD_Card.h"

//A file type to store the file we are writing data to on the SD Card
File datalog_file;

//Two strings one to hold the file name and the other to hold the correct date format
char date[11];
char filename[15];

//Variables to hold the value of the month day and year to be used in setting the date for the title of the CSV file.
int yearI=0;
int monthI=1;
int dayI=2;
int hourI=3;
int minuteI=4;

//Setting up the SD card Module
void SD_setup(){
  //Setting the current date and time
  //      Hour  Minute second month, day, year
  setTime(hourI, minuteI, 0, monthI, dayI, yearI); 
  //Serial.print()
  //Ensuring that the chip select pin intializes.
  //*****NOTICE IF THERE IS NO SD CARD THE ENTIRE PROGRAM WILL NOT RUN
  if(!SD.begin(17)){
    //Letting the user know in the terminal that the
    Serial.println("initialization failed!");
    while(1);
  }
  sprintf(date, "%02d.%02d.%04d", month(), day(), year());
  //Combing that date format with .csv at the end to create the file name and a csv file.
  sprintf(filename, "%s.csv", date);
  //Assiging the file value to open the selected file name in a writer. If it can not find the file it will create the desired csv file.
  datalog_file = SD.open(filename, FILE_WRITE);
  Serial.print("FILE WRITING TO: ");
  Serial.println(filename);
  //Printing the time stamp in the file
    datalog_file.print("Date and Time: ");
    datalog_file.print(", ");
    //PRinting all the relevant variables into the file all seperated by a comma to create a propper CSV file.
    datalog_file.print("External Humidity: ");
    datalog_file.print(", ");
    datalog_file.print("External Temperature: ");
    datalog_file.print(", ");
    datalog_file.print("Internal Humidity: ");
    datalog_file.print(", ");
    datalog_file.print("Internal Temperature: ");
    datalog_file.print(", ");
    datalog_file.print("Solar Irradiance Value");
    datalog_file.print(", ");
    datalog_file.print("Fan Speed percentage (0 - 100): ");
    datalog_file.print(", ");
    datalog_file.print("Vent openening Percentage (0-50):");
    datalog_file.print(", ");
    datalog_file.print("Current Internal EMC: ");
    datalog_file.println(" ");
  //Closing the file
  datalog_file.close();
}

//Functions to set the year month and day by the user input
void setYear(int Input_year){
  yearI=Input_year;
}
void setMonth(int Input_month){
  monthI=Input_month;
}
void setDay(int Input_day){
  dayI=Input_day;
}
void setHour(int Input_hour){
  hourI=Input_hour;
}
void setMinute(int Input_minute){
  minuteI=Input_minute;
}

//A function that creates a file labeled the current date and stores all relavent data in it.
void data_Log(float E_humidity, float E_temperature, float I_humidity, float I_temperature, float irradiance, int fan_Speed, int servo_Value, float internal_EMC){
  //Combining the current month day and year into a variable in the correct format MM.DD.YYYY adding zeros as necessary
  sprintf(date, "%02d.%02d.%04d", month(), day(), year());
  //Combing that date format with .csv at the end to create the file name and a csv file.
  sprintf(filename, "%s.csv", date);
  //Assiging the file value to open the selected file name in a writer. If it can not find the file it will create the desired csv file.
  datalog_file = SD.open(filename, FILE_WRITE);
  Serial.print("FILE WRITING TO: ");
  Serial.println(filename);
  //If the file opens
  if(datalog_file){
    //Printing the time stamp in the file
    datalog_file.print("Current date: ");
    datalog_file.print(month());
    datalog_file.print("/");
    datalog_file.print(day());
    datalog_file.print("/");
    datalog_file.print(year());
    datalog_file.print(" - ");
    datalog_file.print("Current time: ");
    datalog_file.print(hour());
    datalog_file.print(":");
    datalog_file.print(minute());
    datalog_file.print(":");
    datalog_file.print(second());
    datalog_file.print(", ");
    //PRinting all the relevant variables into the file all seperated by a comma to create a propper CSV file.
    datalog_file.print(E_humidity);
    datalog_file.print(", ");
    datalog_file.print(E_temperature);
    datalog_file.print(", ");
    datalog_file.print(I_humidity);
    datalog_file.print(", ");
    datalog_file.print(I_temperature);
    datalog_file.print(", ");
    datalog_file.print(irradiance);
    datalog_file.print(", ");
    datalog_file.print(fan_Speed);
    datalog_file.print(", ");
    datalog_file.print(servo_Value);
    datalog_file.print(", ");
    datalog_file.print(internal_EMC);
    datalog_file.println(" ");
  }
   else{
    //IF the file didnt open printing to the serial
    Serial.println("Error opening File");
  }
  //Closing the file
  datalog_file.close();
}