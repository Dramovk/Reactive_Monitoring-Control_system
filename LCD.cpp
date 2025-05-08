//**********************************************//
//                 LCD DEFINITIONS           //
//File to print all relevantinformation on the LCD

//Including the proper header file
#include "LCD.h"

// Initialize the TFT object
TFT_eSPI tft = TFT_eSPI();

// Variables to display on the LCD
float fanSpeed = 1200;       // Example fan speed (RPM)
int fanSpeedPrintValue=0; //Value printed to LCD
int servoPrintValue=0; //Value printed to LCD
float servoAngle = 45;       // Example servo angle (degrees)
float Extemp = 25;             // Example temperature (Farenheight)
float ExRH = 60;               // Example relative humidity (%)
float Irradiance = 800;      // Example irradiance (W/m^2)
float InTemp = 30;     // Example internal temperature (Farenheight)
float InRH = 55;       // Example internal relative humidity (%)
int EMC_interval = 50000; //Variable to set EMC time
int data_log_interval_LCD=2000; //Variable to set Data log time
bool fahrenheit_LCD = true;

// Setup function to initialize TFT and display title
void LCDStart() {
  //Starting the TFT
  tft.begin();
  tft.setRotation(1); // Set rotation to 3 for landscape mode (horizontal layout)
  tft.fillScreen(TFT_RED); // Clear screen once during setup
}

// Update display with the latest values // does not do any actual display outputs though
void UpdateLCDValues(float speed, float angle, float exTemp, float inTemp, float exRH, float inRH, float Irr, int EMC_internval_in, int data_log_in) {
  //Setting the internal LCD variables equal to those passed in from the main fucntion
  fanSpeed = speed;
  servoAngle = angle;
  Extemp = exTemp;
  ExRH = exRH;
  Irradiance = Irr;
  InTemp = inTemp;
  InRH = inRH;
  EMC_interval = EMC_internval_in;
  data_log_interval_LCD = data_log_in; 
}

void Intro_Set(int set_selector, int year, int month, int day, int hour, int minute, int fahrenheit_value) {
  clearPage(); // clears screen
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3); // Larger text size for titles
  //Loic for setting date and time depending on what is being set
  if (set_selector==1)
  {
    Serial.println("Set Year");
    tft.setCursor(150, 110); // Start closer to the left edge
    tft.print("Set Year:  "+String(year));
    tft.setCursor(150, 140); // Start closer to the left edge
    tft.print("Month:  "+String(month));
    tft.setCursor(150, 170); // Start closer to the left edge
    tft.print("Day:  "+String(day));
    tft.setCursor(150, 200); // Start closer to the left edge
    tft.print("Hour:  "+String(hour));
    tft.setCursor(150, 230); // Start closer to the left edge
    tft.print("Minute:  "+String(minute));
  }
  if (set_selector==2)
  {
    tft.setCursor(150, 110); // Start closer to the left edge
    tft.print("Year:  "+String(year));
    tft.setCursor(150, 140); // Start closer to the left edge
    tft.print("Set Month:  "+String(month));
    tft.setCursor(150, 170); // Start closer to the left edge
    tft.print("Day:  "+String(day));
    tft.setCursor(150, 200); // Start closer to the left edge
    tft.print("Hour:  "+String(hour));
    tft.setCursor(150, 230); // Start closer to the left edge
    tft.print("Minute:  "+String(minute));
  }
  if (set_selector==3)
  {
    tft.setCursor(150, 110); // Start closer to the left edge
    tft.print("Year:  "+String(year));
    tft.setCursor(150, 140); // Start closer to the left edge
    tft.print("Month:  "+String(month));
    tft.setCursor(150, 170); // Start closer to the left edge
    tft.print("Set Day:  "+String(day));
    tft.setCursor(150, 200); // Start closer to the left edge
    tft.print("Hour:  "+String(hour));
    tft.setCursor(150, 230); // Start closer to the left edge
    tft.print("Minute:  "+String(minute));
  }
  if (set_selector==4)
  {
    tft.setCursor(150, 110); // Start closer to the left edge
    tft.print("Year:  "+String(year));
    tft.setCursor(150, 140); // Start closer to the left edge
    tft.print("Month:  "+String(month));
    tft.setCursor(150, 170); // Start closer to the left edge
    tft.print("Day:  "+String(day));
    tft.setCursor(150, 200); // Start closer to the left edge
    tft.print("Set Hour:  "+String(hour));
    tft.setCursor(150, 230); // Start closer to the left edge
    tft.print("Minute:  "+String(minute));
  }
  if (set_selector==5)
  {
    tft.setCursor(150, 110); // Start closer to the left edge
    tft.print("Year:  "+String(year));
    tft.setCursor(150, 140); // Start closer to the left edge
    tft.print("Month:  "+String(month));
    tft.setCursor(150, 170); // Start closer to the left edge
    tft.print("Day:  "+String(day));
    tft.setCursor(150, 200); // Start closer to the left edge
    tft.print("Hour:  "+String(hour));
    tft.setCursor(150, 230); // Start closer to the left edge
    tft.print("Set Minute:  "+String(minute));
  }
  if (set_selector==6)
  {
    tft.setCursor(30, 110); // Start closer to the left edge
    tft.print(" Fahrenheit or Celsius:  ");
    tft.setCursor(50, 160);
    tft.print("Temperature shown in: ");
    tft.setCursor(110, 270);
    tft.print( "C <---   ---> F");
    if(fahrenheit_value > 2000)
    {
      fahrenheit_LCD = false;
      tft.setCursor(150, 200);
      tft.print("  Celsius");
    }
    else
    {
      fahrenheit_LCD = true;
      tft.setCursor(150, 200);
      tft.print(" Fahrenheit");
    }
  }
}

//Function for automatic mode
void automaticGUI() {
  clearPage();
  //delay(1000);
  //Display the necessary variables on the screen
  displayVariables(fanSpeed, servoAngle, Extemp, ExRH, Irradiance, InTemp, InRH);
  //Displaying the titles for those values
  displayTitles(1);
}

//Function for manual mode
void manualGUI()
{
  clearPage();
  //Display the necessary variables on the screen
  displayVariables(fanSpeed, servoAngle, Extemp, ExRH, Irradiance, InTemp, InRH);
  //Displaying the titles for those values
  displayTitles(0);
  //Display actuators
  displayFan_Orifice();
}

//Functional for adjust parameters mode
void adjustParametersGUI()
{
  clearPage();
  //Display the necessary variables on the screen
  displayVariables(fanSpeed, servoAngle, Extemp, ExRH, Irradiance, InTemp, InRH);
  //Displaying the titles for those values
  displayTitles(2);
  //Display set EMC time, and Data logging time
  display_EMC_dLog_Time();
}

//Displaying EMC time, Celcius or farenheight and Data logging time.
void display_EMC_dLog_Time()
{
  int xmid = 300;
  int ymid = 85;
  tft.drawRect(xmid+15, ymid, xmid + 30, ymid + 125, TFT_WHITE);
  tft.setTextSize(2);  // Larger text size for data
  
  // Display Set Fan label
  tft.setCursor(xmid + 20, ymid + 35);
  tft.print("Set EMC");
  tft.setCursor(xmid + 17, ymid + 65);
  tft.print("Interval(min)");

  // Display fan value underneath
  tft.setCursor(xmid + 20, ymid + 85);
  tft.print(EMC_interval);
  
  // Display Set Servo label
  tft.setCursor(xmid + 20, ymid + 115);
  tft.print("Set Data Log");
  tft.setCursor(xmid + 17, ymid + 145);
  tft.print("Interval(min)");

  // Display servo value underneath
  tft.setCursor(xmid + 20, ymid + 165);
  tft.print(data_log_interval_LCD);
}

//Displaying the fan and servo for manual mode when they are being set.
void displayFan_Orifice()
{
  //TRYING TO TAKE THESE OUT
  //fanSpeed = fan;
  //servoAngle = orifice*2.5;
  int xmid = 300;
  int ymid = 85;
  tft.drawRect(xmid+15, ymid, xmid + 30, ymid + 125, TFT_WHITE);
  tft.setTextSize(2);  // Larger text size for data
  
  // Display Set Fan label
  tft.setCursor(xmid + 20, ymid + 35);
  tft.print("Set Fan:");
  
  // Display fan value underneath
  tft.setCursor(xmid + 20, ymid + 55);
  tft.print(fanSpeed);
  
  // Display Set Servo label
  tft.setCursor(xmid + 20, ymid + 85);
  tft.print("Set Servo:");
  
  // Display servo value underneath
  tft.setCursor(xmid + 20, ymid + 105);
  tft.print(servoAngle);
}

// Function to clear only the necessary parts of the screen
void clearPage() {
  // Clear the entire screen to avoid old data lingering
  tft.fillScreen(TFT_BLACK);
}

// Display titles on the screen
void displayTitles(int v) {
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3); // Larger text size for titles
  tft.setCursor(20, 50); // Start closer to the left edge
  tft.print("Environmental Variables:");
  tft.drawLine(0,80,500,80,TFT_WHITE);

  // Display "Dryer Status" on the right side
  tft.setTextSize(3); // Same size text for the status
  tft.setCursor(20, 20);  // Start at the midpoint for the second column
  if(v==1)
    tft.print("Mode:  Automatic");
  if(v==0)
    tft.print("Mode:  Manual");
  if(v ==2)
    tft.print("Mode:  Adjust Parameters");
}

void displayVariables(float speed, float angle, float exTemp, float inTemp, float exRH, float inRH, float Irr) {
  int x = 20;  // Left column starting X position
  int y = 90; // Start below the title
  int spacing = 30; // More space between rows for larger text
  
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);  // Larger text size for data
  tft.drawRect(x-5,y-5,x+280,y+120,TFT_WHITE);
  
  // Left column
  tft.setCursor(x, y);
  tft.print("Fan Speed : ");
  fanSpeedPrintValue = map(fanSpeed, 75, 100, 0, 100); //CHECK TO SEE IF RIGHT
  tft.print(fanSpeedPrintValue);
  tft.println(" %");

  y += spacing;
  tft.setCursor(x, y);
  tft.print("Outlet Open: ");
  servoPrintValue = map(servoAngle, 0, 255, 0, 100);// CHECK TO SEE IF RIGHT
  tft.print(servoPrintValue);
  tft.println(" %");

  y += spacing;
  tft.setCursor(x, y);
  tft.print("External Temp: ");
  tft.print(Extemp);
  if(fahrenheit_LCD)
  {
    tft.println(" F");
  }
  else
  {
    tft.println(" C");
  }

  y += spacing;
  tft.setCursor(x, y);
  tft.print("Internal Temp: ");
  tft.print(InTemp);
  if(fahrenheit_LCD)
  {
    tft.println(" F");
  }
  else
  {
    tft.println(" C");
  }

  y += spacing;
  tft.setCursor(x, y);
  tft.print("External RH: ");
  tft.print(ExRH);
  tft.println(" %");

  y += spacing;
  tft.setCursor(x, y);
  tft.print("Internal RH: ");
  tft.print(InRH);
  tft.println(" %");

  y += spacing;
  tft.setCursor(x, y);
  tft.print("Irradiance: ");
  tft.print(Irradiance);
  tft.println(" W/m^2");
}
