/*
    ElviraMove.h - header file for functions that allow joint articulation for Elvira
*/

#ifndef Elvira_h
#define Elvira_h

#include "Arduino.h"
#include "stdint.h"
#include "Wire.h"

void PWMGen(uint8_t driverAddress, uint8_t motorID, uint8_t positionDeg); 

class Leg
{
    public:
    uint8_t shoulderJoint;
    uint8_t topJoint;
    uint8_t bottomJoint;
    uint8_t driverAddress;
    Leg(uint8_t shoulder, uint8_t top, uint8_t bottom);
    void sweep(uint8_t);  
    void straighten(); 


};

class PCA9685
{
    public:
    PCA9685(uint8_t address);
    void driverWrite(uint8_t driverAddress, uint8_t regID, uint8_t value);    
};




#endif
