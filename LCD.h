#ifndef LCD_H
#define LCD_H

// Define LCD pins 
/***********************************
  IMPORTANT THESE PINS MUST BE REFLECTED IN THE TFT_eSPI.H FILE LOCAL ON YOUR COMPUTER
LCD SCREEN PINS
 TFT_CS     5   // Chip Select (CS)
 TFT_DC     6   // Data Command (DC)
 TFT_MOSI   3   // SPI MOSI (DIN)
 TFT_CLK    2   // SPI Clock (CLK)
 TFT_RST    4   // Reset (RST)
*******************************************/
// Include the TFT_eSPI library
#include <TFT_eSPI.h>  

//A function that starts and sets up the LCD display
void LCDStart();

// A function that updates the display with the latest values
void UpdateLCDValues(float speed, float angle, float t1, float t2, float Rh1, float Rh2, float Irr);

// runs the Intro date set windows
void Intro_Set(int set_selector, int year, int month, int day, int hour, int minute);

// Automatic GUI
void automaticGUI();

// Manual GUI
void manualGUI();

// Displays actuators (not directly called)
void displayFan_Orifice(int fan, int orifice);

// Function to clear only the necessary parts of the screen
void clearPage();

// A function to display the titles on the screen
void displayTitles(int v);

// A function to display values on the screen in two columns
void displayVariables(float speed, float angle, float exTemp, float inTemp, float exRH, float inRH, float Irr);

#endif