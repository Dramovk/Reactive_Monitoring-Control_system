# 🌞 Reactive Monitoring and Control System Software

This software is designed for use with the **Active Portable Solar Crop Dryer** and the control system detailed in the *Reactive Monitoring and Control System Technical Manual*.

It continuously reads and stores key environmental variables — including:

- Internal temperature and humidity
- External temperature and humidity
- Internal solar irradiance

All this data, along with the **target drying temperature** (calculated based on the current internal temperature and equilibrium moisture content equation), is formatted and saved to a **CSV file on an SD card**.

---

## 🔧 System Functionality

- Stores environmental and control data with timestamps (year, month, day, hour, minute)
- Controls:
  - **Servo** for the louvered vent
  - **Fan speed**
- Implements a **reactive control algorithm** to help the dryer reach and maintain optimal drying conditions

---

## 📦 Prerequisites

To build and upload this code, you’ll need the following:

- [Arduino IDE](https://www.arduino.cc/en/software)
- Raspberry Pi Pico (RP2040 board)
- Required libraries:
  - `TFT_eSPI`
  - `Servo.h`
  - `SHT` (for SHT30 sensor)
  - `DHT` (for DHT22 sensor)
  - `SD` or `SD_MMC` (for SD card logging)

Make sure the Raspberry Pi Pico board package is installed in your Arduino IDE.

---

## 🚀 How to Run

1. Plug your computer into the **Raspberry Pi Pico** using a USB cable  
2. Open the code in Arduino IDE  
3. Select the correct board and port  
4. Press **Upload** to compile and run the code on the device  

---

## 📁 File Structure

Each module contains a `.h` and a `.cpp` file with the same name (except for the main file):

| File / Module            | Description |
|--------------------------|-------------|
| `External_SHT30_Sensor`  | Handles external humidity and temperature readings |
| `Internal_DHT22_Sensor`  | Reads internal temperature and humidity |
| `Irradiance_Sensor`      | Reads solar irradiance inside the dryer |
| `Fan_Control`            | Controls fan speed based on reactive logic |
| `Servo_Control`          | Controls the louvered vent position |
| `Reactive_Algorithm`     | Core reactive control logic for target temperature |
| `SD_Card`                | Manages CSV data logging on the SD card |
| `LCD`                    | Manages data display on the TFT screen |
| `ReactiveControlTeamCode2` | Main file that brings everything together |

---

## 💡 Usage Examples *(To Be Added)*

> Here’s where you can show example outputs or screenshots. Things you might want to include:
> 
> - Sample output from the CSV log  
> - Photos of the TFT screen during operation  
> - Code snippets showing how the fan/servo responds to sensor inputs  
> - Diagram of the sensor/control wiring setup  
> 
> 📌 *Let me know if you'd like help formatting any of this when you're ready to add it!*

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).  
You are free to use, modify, and distribute this code for personal or commercial use, provided that proper credit is given.

---
