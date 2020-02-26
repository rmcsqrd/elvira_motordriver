/*
    ElviraMove.cpp - Library for functions that allow joint articulation for Elvira
*/

#include "Arduino.h"
#include "Elvira.h"
#include "stdint.h"
#include "Wire.h"

TwoWire myWire(3); // use pins 42/43 (16 = SDA, 17=SCL on Artemis thing plus)
PCA9685 motorDrive((uint8_t)0x40);

void PWMGen(uint8_t driverAddress, uint8_t motorID, uint8_t positionDeg){
      /* MotorID = PWM Pin (0-15)
     positionDeg = degrees of rotation (0-180)

     determine pin # (pin 0 = 6, 4 registers per pin, thus:
                      pinONL = 6+Pin#*4+0           
                      pinONH = 6+Pin#*4+1           
                      pinOFFL = 6+Pin#*4+2           
                      pinOFFH = 6+Pin#*4+3     

  */

  // set up registers to write to
  uint8_t pinOFFL = 6+motorID*4+0;  // I know they're swapped but it just works idk
  uint8_t pinOFFH = 6+motorID*4+1;
  uint8_t pinONL = 6+motorID*4+2;
  uint8_t pinONH = 6+motorID*4+3;

  // determine degrees of rotation
  float rotateVal = 0.5*(1+(float)positionDeg/180);  // 0.5 makes it work for some reason

  // adjust values to write to registers with some bitwise manipulation
  uint16_t LEDON = 4095*rotateVal/20;
  uint16_t LEDOFF = 4095*(20-rotateVal)/20;
  
  uint8_t LEDONL = LEDON;       // casting to an int takes care of low bit
  uint8_t LEDONH = LEDON >> 8;  // bitwise shift then cast to int for high bit 
  
  uint8_t LEDOFFL = LEDOFF;
  uint8_t LEDOFFH = LEDOFF >> 8;

  uint8_t pin[] = {pinONL, pinONH, pinOFFL, pinOFFH};
  uint8_t value[] = {LEDONL, LEDONH, LEDOFFL, LEDOFFH};

  for(int cnt = 0; cnt < 4; cnt++){
    myWire.beginTransmission(driverAddress);
    myWire.write(pin[cnt]);
    myWire.write(value[cnt]);
    myWire.endTransmission();
  }
}



Leg::Leg(uint8_t shoulder, uint8_t top, uint8_t bottom)
{
    shoulderJoint = shoulder;
    topJoint = top;
    bottomJoint = bottom;
    driverAddress = 0x40;
}

void Leg::sweep(uint8_t degree){
    PWMGen(driverAddress, shoulderJoint, degree);
}

void Leg::straighten(){
    PWMGen(driverAddress, topJoint, 90);
    PWMGen(driverAddress, bottomJoint, 90);
}

void Leg::articulate(uint8_t topdeg, uint8_t botdeg){
    PWMGen(driverAddress, topJoint, topdeg);
    PWMGen(driverAddress, bottomJoint, botdeg);
}

    
PCA9685::PCA9685(uint8_t address)
{
    uint8_t driverAddress = address;
    myWire.begin();

    // put in sleep mode to write prescale, write prescale, out of sleep mode
    // adjust prescaler for 20Hz duty cycle (per MG90S datasheet)
    // use prescale value = 122 = 25MHz/(4096*50)-1 (per PCA9685 datasheet, page 24)
    driverWrite(0x40, 0x00, 0x11);
    driverWrite(0x40, 0xFE, 129);
    driverWrite(0x40, 0x00, 0x01);

}

void PCA9685::driverWrite(uint8_t driverAddress, uint8_t regID, uint8_t value){
    myWire.beginTransmission(driverAddress);
    myWire.write(regID);
    myWire.write(value);
    myWire.endTransmission();
}

Body::Body()
{
    leg1Top = 2;
    leg1Bottom = 1;
    leg2Top = 8;
    leg2Bottom = 7;
    leg3Top = 5;
    leg3Bottom = 4;
    leg4Top = 11;
    leg4Bottom = 10;
    driverAddress = 0x40;
}

uint8_t Body::degreeConvert(float degrees){
   uint8_t unsigned_degrees = degrees*90 + 90; // technically degrees is a bit of a misnomer but I don't want to refactor 
   return unsigned_degrees;
}

void Body::pitch(float degrees){
    uint8_t us_degrees = degreeConvert(degrees); // convert so plays nice with PWMGen but also intuitive
    PWMGen(driverAddress, leg1Top, 180-us_degrees);  // legs (1,4) and (2,3) have opposite actuation mechanisms, we send PWM signals accordingly.
    PWMGen(driverAddress, leg1Bottom, 180-us_degrees);

    PWMGen(driverAddress, leg2Top, us_degrees);
    PWMGen(driverAddress, leg2Bottom, us_degrees);
    
    PWMGen(driverAddress, leg3Top, 180-us_degrees);
    PWMGen(driverAddress, leg3Bottom, 180-us_degrees);

    PWMGen(driverAddress, leg4Top, us_degrees);
    PWMGen(driverAddress, leg4Bottom, us_degrees);
}

void Body::roll(float degrees){
    uint8_t us_degrees = degreeConvert(degrees);
    PWMGen(driverAddress, leg1Top, us_degrees);
    PWMGen(driverAddress, leg1Bottom, us_degrees);
    
    PWMGen(driverAddress, leg2Top, us_degrees);
    PWMGen(driverAddress, leg2Bottom, us_degrees);
    
    PWMGen(driverAddress, leg3Top, 180-us_degrees);
    PWMGen(driverAddress, leg3Bottom, 180-us_degrees);
    
    PWMGen(driverAddress, leg4Top, 180-us_degrees);
    PWMGen(driverAddress, leg4Bottom, 180-us_degrees);
}





