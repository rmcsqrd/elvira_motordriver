// include
#include <Wire.h>
TwoWire myWire(3); //Will use pads 42/43

void setup() {
  myWire.begin();  // initialize i2c stuff
  pinMode(2, OUTPUT);
}
byte val = 0;

void loop() {
  myWire.beginTransmission(0xF0);
  uint8_t error = Wire.endTransmission();
  digitalWrite(2, HIGH);
  delay(250);
  digitalWrite(2, LOW);
  delay(250);
}
