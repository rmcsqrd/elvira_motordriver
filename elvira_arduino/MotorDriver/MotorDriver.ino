/* Motor Driver for Elvira V
 * 
 */

 
#include "Wire.h"
#include <stdint.h>
//#include <//Users/riomcmahon/Programming/Elvira/elvira/elvira_arduino/MotorDriver/Elvira.h>
//#include "Elvira.h"
#include "src/MotorDriverLib/Elvira.h"

/*   ASCII Schematic (Plan View)
 *        1  F   2
 *         \ * /
 *          [ ]
 *         /   \
 *        3     4
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


// CONSTRUCT THE LEGS
Leg leg1(0,2,1);
Leg leg2(6,8,7);
Leg leg3(3,5,4);
Leg leg4(9,11,10);

// Define movement delay
uint16_t delayt = 1000;

void setup() {
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


void loop() {
//  leg2.articulate(90,90);  // 2 up
//  leg1.articulate(00,00);  // 1 up
//  leg3.articulate(90,90);  // 3 up
//  leg4.articulate(00,00);  // 4 up

//  getshort();
//  forward(1);
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

void pushups(){
  leg1.articulate(180,0);
  leg2.articulate(0,180);
  leg4.articulate(180,0);
  leg3.articulate(0,180);
  delay(delayt);
  leg1.articulate(180,180);
  leg2.articulate(0,0);
  leg4.articulate(180,180);
  leg3.articulate(0,0);
  delay(delayt);
}

void gettall(){
  leg1.articulate(180,180);
  leg2.articulate(0,0);
  leg4.articulate(180,180);
  leg3.articulate(0,0);
}

void getshort(){
  leg1.articulate(0,0);
  leg2.articulate(180,180);
  leg4.articulate(0,0);
  leg3.articulate(180,180);
}
