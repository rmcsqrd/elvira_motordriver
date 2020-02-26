/* Motor Driver for Elvira V
 * 
 */

// include stuff
#include "Wire.h"
#include <stdint.h>
#include "src/MotorDriverLib/Elvira.h"
#include "math.h"

/*   ASCII Schematic (Plan View, numbers indicate leg #)
 *        1  F   2     z
 *         \ * /       |_ x
 *          [ ]         
 *         /   \
 *        3     4
 *        
 *  ASCII Schematic (Section View, from back)     
 *    
 *        /\[ ]/\      y
 *       /       \     |_ x
 *       
 *       
 *  Rotation Definitions
 *  Yaw   = My (how it changes directions, ∈[0, 2pi], F is 0, 2pi and increases clockwise)
 *  Pitch = Mx (lean forward or backward, ∈[-1, 1], 0 is aligned with yaxis. +CW, -CCW)
 *  Roll  = Mz (lean side to side, ∈[-1. 1], 0 is aligned with yaxis. +forward, -backward CCW)
 *  
 *  
 *  Servo Map
 *  LEG | Shoulder, Top, Bottom
 *  1   | 0, 2, 1
 *  2   | 6, 8, 7
 *  3   | 3, 5, 4
 *  4   | 9, 11, 10
 *  
 *  (Top is top of leg actuator, bottom is bottom of leg actuator)
 *  
 *  General Notes:
 *  - 20ms delay is approximate min for servo refresh, any lower causes eratic behavior
 */

// Constructors
// CONSTRUCT THE LEGS
Body body;

Leg leg1(0,2,1);
Leg leg2(6,8,7);
Leg leg3(3,5,4);
Leg leg4(9,11,10);




// Define globals
// Define movement delay
uint16_t delayt = 1000;


// Initialize Routine
void setup() {
  uint8_t timestep = 100;
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  sayHello(2);

  delay(delayt);


  delay(delayt);
  
  leg4.articulate(0,0);  // step leg 4, and bring leg 2 to parallel
  leg1.articulate(0,0);
  delay(timestep);
  leg4.sweep(180);
  leg2.sweep(180);
  delay(timestep);
  leg4.articulate(180,180);
  leg1.articulate(180,180);
  delay(delayt);


  leg2.articulate(180,180);  // step leg 2, drop leg 3 hip
  leg3.articulate(180,180);
  delay(timestep);
  leg2.sweep(0);
  leg4.sweep(0);
  delay(timestep);
  leg2.articulate(0,0);
  leg3.articulate(0,0);
  delay(delayt);

  leg3.articulate(180,180);  // step leg 3, and bring leg 1 to parallel
  leg2.articulate(180,180);
  delay(timestep);
  leg3.sweep(00);
  leg1.sweep(0);
  delay(timestep);
  leg3.articulate(0,0);
  leg2.articulate(0,0);
  delay(delayt);

  leg1.articulate(180,180);  // step leg 2, drop leg 3 hip
  leg4.articulate(180,180);
  delay(timestep);
  leg1.sweep(0);
  leg3.sweep(0);
  delay(timestep);
  leg1.articulate(0,0);
  leg4.articulate(0,0);
  delay(delayt);
  

  


  
}

// Main Loop
void loop() {
}

// Auxillary Functions


void stanceReset(){
  leg1.straighten();
  leg2.straighten();
  leg3.straighten();
  leg4.straighten();
  gettall();
  leg1.sweep(180);
  leg2.sweep(0);
  leg3.sweep(180);
  leg4.sweep(0);
}

void sayHello(uint8_t n){
  stanceReset();
  int pushupTime = 200;
  for(int i =0; i<n;i++){
    leg1.articulate(180,0);
    leg2.articulate(0,180);
    leg4.articulate(180,0);
    leg3.articulate(0,180);
    digitalWrite(4, LOW);
    delay(pushupTime);
    leg1.articulate(180,180);
    leg2.articulate(0,0);
    leg4.articulate(180,180);
    leg3.articulate(0,0);
    digitalWrite(4, HIGH);
    delay(pushupTime);
  }
}

void gettall(){
  leg1.articulate(180,180);
  leg2.articulate(0,0);
  leg4.articulate(180,180);
  leg3.articulate(0,0);
}

void getmiddle(){
  leg1.articulate(90,90);
  leg2.articulate(90,90);
  leg4.articulate(90,90);
  leg3.articulate(90,90);
}

void getshort(){
  leg1.articulate(0,0);
  leg2.articulate(180,180);
  leg4.articulate(0,0);
  leg3.articulate(180,180);
}
