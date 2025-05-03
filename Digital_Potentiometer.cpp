#include "Digital_Potentiometer.h"


//Function that sets up the digital potentiometer to control DC motor controller
void digital_Potentiometer_Setup() {
  pinMode(DPOT_INC_PIN, OUTPUT);// initalizing the INC pin
  pinMode(DPOT_UD_PIN, OUTPUT);// initalizing the UD pin
  pinMode(DPOT_CS_PIN, OUTPUT);// initalizing the CS pin

  digitalWrite(DPOT_INC_PIN, HIGH);//initalizing the inc pin
  digitalWrite(DPOT_CS_PIN, HIGH);// initalizing the cs pin
}

// void loop() {
//   for (int percent = 70; percent <= 100; percent += 1) {
//     setPotPosition(percent);
//     Serial.print("Set to ");
//     Serial.print(percent);
//     Serial.println("%");
//     delay(2000);
//   }

//   delay(2000);

//   for (int percent = 100; percent >= 70; percent -= 1) {
//     setPotPosition(percent);
//     Serial.print("Set to ");
//     Serial.print(percent);
//     Serial.println("%");
//     delay(2000);
//   }

//   delay(2000);
// }

// === Always reset to 0 then step up ===
void set_Motor_Speed(int percent) {
  percent = constrain(percent, 0, 100);
  int steps = map(percent, 0, 100, 99, 0);

  // Step down all the way first to ensure known position
  digitalWrite(DPOT_UD_PIN, LOW);
  digitalWrite(DPOT_CS_PIN, LOW);
  for (int i = 0; i < 100; i++) {
    pulseInc();
  }
  digitalWrite(DPOT_CS_PIN, HIGH);

  // Now step up to target
  digitalWrite(DPOT_UD_PIN, HIGH);
  digitalWrite(DPOT_CS_PIN, LOW);
  for (int i = 0; i < steps; i++) {
    pulseInc();
  }
  digitalWrite(DPOT_CS_PIN, HIGH);
}

//pilsong the increment pin
void pulseInc() {
  digitalWrite(DPOT_INC_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(DPOT_INC_PIN, HIGH);
  delayMicroseconds(5);
}
