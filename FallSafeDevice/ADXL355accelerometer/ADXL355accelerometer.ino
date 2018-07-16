/*
  The circuit:
  - analog 1: ground
  - analog 2: z-axis
  - analog 3: y-axis
  - analog 4: x-axis
  - analog 5: vcc

  zero g is 1/3 of max value, ie 341 in case of 10bit ADC in arduino (341/1024)
  273 is one g following the given axis --> +1g
  411 is one g opposite to the given axis --> -1g

  ie, a difference of -68 from zero value is +1g
  also, a difference of 68 from zero value is -1g
  
*/
#include "adxl355.h"
// these constants describe the pins. They won't change:
const int groundpin = A1;             // analog input pin 4 -- ground
const int powerpin = A5;              // analog input pin 5 -- voltage
const int xpin = A4;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)
const int airbagPinBack = 7;
const int airbagPinFwd = 8;

//create the accelerometer object
class adxl355 acm(100, xpin, ypin, zpin);

void setup(){
  // initialize the serial communications:
  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  pinMode(airbagPinFwd, OUTPUT);
  pinMode(airbagPinBack, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  delay(500);
}

  void loop(){
  acm.set_orientation();
  acm.update_values();
  if(!acm.fall_triggered && acm.is_falling()){
    if(acm.orientation_direction == 1 || acm.orientation_direction == 3)
      digitalWrite(airbagPinFwd, HIGH);
    if(acm.orientation_direction == 2 || acm.orientation_direction == 4)
      digitalWrite(airbagPinBack, HIGH);
    Serial.println("Falling "+acm.get_orientation());
    Serial.print(acm.fall_triggered);
  }
  else if(!acm.fall_triggered){
    Serial.print(acm.get_orientation()+"  ");
    Serial.print(acm.rms_acceleration()); Serial.print("  ");
    acm.display_values();
  }
}

