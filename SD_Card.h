#ifndef SD_CARD_H
#define SD_CARD_H

//Library inclusions for the SD card module
#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>

/************************************************************
  IMPOTANT THE PINS HAVE TO BE SET UP ON THE SAME SPI CHANNEL AS THE CHIP SELECT PIN--17.
************************************************************/

/*SD card attached to SPI bus as follows:
  MOSI - pin 19
  MISO - pin 16
  CLK - pin 18
  CS - pin 17 */

//A function to setup the SD card module
void SD_setup(bool farenheight);

//A function to log all the data onto the SD card in a CSV file format
void data_Log(float E_humidity, float E_temperature, float I_humidity, float I_temperature, float irradianceint, int fan_Speed, int servo_Value, float internal_TargetTemp);

void setYear(int year);
void setMonth(int month);
void setDay(int day);
void setHour(int hour);
void setMinute(int minute);
#endif