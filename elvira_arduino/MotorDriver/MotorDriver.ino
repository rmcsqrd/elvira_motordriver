/* Motor Driver for Elvira V
 * 
 */

// include stuff
#include "Wire.h"
#include <stdint.h>
#include "src/MotorDriverLib/Elvira.h"

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
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  sayHello(2);
  body.Roll(-1);
  delay(delayt);
  standtall();
  delay(delayt);
  body.Roll(1);
  delay(delayt);
  standtall();
  delay(delayt);
  body.Pitch(-1);
  delay(delayt);
  standtall();
  delay(delayt);
  body.Pitch(1);
  delay(delayt);
  standtall();
}

// Main Loop
void loop() {
//  prance(3);
//  leg2.articulate(180,180);
//  leg1.articulate(90,180);  // 1 up
//  leg4.articulate(180,0);  // 1 up
//  leg3.articulate(0,180);  // 3 up
    
  
  
}

// Auxillary Functions
void prance(uint8_t n){
  for(int i =0; i<n;i++){
    leg3.articulate(0,0);  // 3 up
    delay(delayt);
    leg3.articulate(180,180);  // 3 down
    leg1.articulate(180,180); // 1 up
    delay(delayt);
    leg1.articulate(0,0); // 1 down
    leg2.articulate(0,0); // 2 up
    delay(delayt);
    leg2.articulate(180,180); // 2 down
    leg4.articulate(180,180); // 4 up
    delay(delayt);
    leg4.articulate(0,0); // 4 down;
  }
}


void randomArticulate(uint8_t n){
  for(int i =0; i<n;i++){
    leg3.articulate(0,0);  // 3 up
    delay(delayt);
    leg3.articulate(180,180);  // 3 down
    leg1.articulate(0,0); // 1 up
    delay(delayt);
    leg1.articulate(180,180); // 1 down
    leg2.articulate(0,0); // 2 up
    delay(delayt);
    leg2.articulate(180,180); // 2 down
    leg4.articulate(180,180); // 4 up
    delay(delayt);
    leg4.articulate(0,0); // 4 down;
  }
}



void forward(uint8_t numSteps){
  for(uint8_t stepcnt = 0; stepcnt < numSteps; stepcnt++){
    leg4.articulate(0,0);  // 4 up
    leg4.sweep(180);
    leg4.articulate(90,90);  // 4 down
    
    delay(delayt);

    leg2.articulate(90,90);  // 2 up
    leg2.sweep(180);
    leg2.articulate(0,0);  // 2 up

    delay(delayt);

    leg3.articulate(90,90);  // 3 up
    leg3.sweep(0);
    leg3.articulate(0,0);  // 3 down

    delay(delayt);

    leg1.articulate(0,0);  //1 up
    leg1.sweep(0);
    leg1.articulate(90,90);  //1 down
    
    //_____________
leg4.articulate(0,0);  // 4 up
    leg4.sweep(0);
    leg4.articulate(90,90);  // 4 down
    
    delay(delayt);

    leg2.articulate(90,90);  // 2 up
    leg2.sweep(0);
    leg2.articulate(0,0);  // 2 up

    delay(delayt);

    leg3.articulate(90,90);  // 3 up
    leg3.sweep(180);
    leg3.articulate(0,0);  // 3 down

    delay(delayt);

    leg1.articulate(0,0);  //1 up
    leg1.sweep(180);
    leg1.articulate(90,90);  //1 down

    delay(delayt);

  }
}



void standtall(){
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

void tiltDance(){
//  getmiddle();
  getshort();
  delay(delayt);
  leg1.articulate(0,0);     // lean forward
  leg2.articulate(180,180);
  leg3.articulate(0,0);
  leg4.articulate(180,180);
  delay(delayt);  
  getshort();
  delay(delayt);
  leg3.articulate(180,180);     // lean backward
  leg4.articulate(0,0);

  leg1.articulate(180,180);   
  leg2.articulate(0,0);
  delay(delayt);
  getshort();
  delay(delayt);
  leg3.articulate(180,180);     // lean left
  leg1.articulate(0,0);

  leg2.articulate(0, 0);
  leg4.articulate(180,180);
  delay(delayt);
  getshort();
  delay(delayt);
  
  leg2.articulate(180,180);     // lean right
  leg4.articulate(0,0);

  leg1.articulate(180,180);
  leg3.articulate(0,0);
  delay(delayt);
  standtall();
  delay(delayt);
  getmiddle();
  delay(delayt);
  getshort();
  delay(delayt);
  getmiddle();
  delay(delayt);
  standtall();
  delay(delayt);

}
