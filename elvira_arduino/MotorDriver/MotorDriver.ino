/* Motor Driver for Elvira V
 * 
 */

 
#include "Wire.h"
#include <stdint.h>
#include "Elvira.h"


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

void setup() {
  leg1.straighten();
  leg2.straighten();
  leg3.straighten();
  leg4.straighten();
}


void loop() {
  leg1.sweep(180);
  leg2.sweep(180);
  leg3.sweep(0);
  leg4.sweep(0);
  delay(1000);
  leg1.sweep(0);
  leg2.sweep(0);
  leg3.sweep(180);
  leg4.sweep(180);
  delay(1000);
  
}
