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
 // class for individual leg related functionality
    public:
    uint8_t shoulderJoint;
    uint8_t topJoint;
    uint8_t bottomJoint;
    uint8_t driverAddress;
    Leg(uint8_t shoulder, uint8_t top, uint8_t bottom);
    void sweep(uint8_t);  
    void straighten(); 
    void articulate(uint8_t, uint8_t);

};

class PCA9685
{
    public:
    PCA9685(uint8_t address);
    void driverWrite(uint8_t driverAddress, uint8_t regID, uint8_t value);    
};

class Body
{
// class for overall body movement (mostly controls joint articulation, not sweep)

    public:
    uint8_t leg1Top;
    uint8_t leg1Bottom;
    uint8_t leg2Top;
    uint8_t leg2Bottom;
    uint8_t leg3Top;
    uint8_t leg3Bottom;
    uint8_t leg4Top;
    uint8_t leg4Bottom;
    uint8_t driverAddress;
    Body();
    void yaw(uint16_t degrees);
    void pitch(float degrees);
    void roll(float degrees);
    uint8_t degreeConvert(float degrees);
};
#endif
