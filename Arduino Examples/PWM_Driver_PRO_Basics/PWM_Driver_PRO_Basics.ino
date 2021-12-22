/* Project FOD-PWM driver PRO(bidirection)
 * 
 * PWM Driver PRO module is an H-bridge driver in essence, 
 * which can control bi-directional loads (DC motors, Petier Pads, etc.) with positive or negative direction through BI and FI two-way PWM.
 * 
 * Connect any Arduino PWM capable PIN to the BI/FI pin of the module, and the Arduino GND to the module GND, 
 * Then the bidirectional load(fans, heating pads, etc.) can be drived to 
 * any +INTENSITY(from 0 to 255, min to max) by analogWrite(FIpin, INTENSITY);
 * or any -INTENSITY(from 0 to 255, min to max) by analogWrite(BIpin, INTENSITY);
 * For example, to control the fan blowing or suction.
 * 
 * The PINs definition of the module is similar to the three-wire interface (IN/OUT, 5V, GND) commonly used in the Arduino external sensing/output modules, 
 * but for the purpose of direct button control, the VIN Pin here is provided by the battery or other power supplies directly connected to the module.
 * Therefore, only BI, FI and GND should be connected when using the Arduino to control the module, to avoid a reverse breakdown of the Arduino 
 * due to inconsistency with the on-chip power supply level of the Arduino.
 * 
 * NOTICE: When switching between positive and negative, a certain amount of time delay is necessary, otherwise the circuit or load will be damaged.
 * 
 * The analogWrite() function uses PWM, so if you want to change the pin you're
   using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
   are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.
 * 
 * 
 * Copyright (c) 2021 Anonymous for submission.
 * 
*/
int FI = 9;           // the PWM pin the driver FI pin is attached to
int BI = 10;          // the PWM pin the driver BI pin is attached to
int intensity = 0;  
int steplength = 5;    
void setup() {
  // initialize the digital pin as an output.
  pinMode(FI, OUTPUT);
  pinMode(BI, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  for (int intensity = 0; intensity < 255; intensity = intensity + steplength) {
    analogWrite(FI, intensity);
    delay(30);
  }
  // wait a second at the top:
  delay(100);
  // change the resistance on this channel from max to min:
  for (int intensity = 0; intensity < 255; intensity = intensity + steplength) {
    analogWrite(FI, 255-intensity);
    delay(30);
  }
  //***IMPORTANT***
  delay(10000);//A long time delay is needed to wait for the load to stop. Then turn it on to the opposite direction.
  
  for (int intensity = 0; intensity < 255; intensity = intensity + steplength) {
    analogWrite(BI, intensity);
    delay(30);
  }
  // wait a second at the top:
  delay(100);
  // change the resistance on this channel from max to min:
  for (int intensity = 0; intensity < 255; intensity = intensity + steplength) {
    analogWrite(FI, 255-intensity);
    delay(30);
  }
  delay(10000);//A long time delay is needed to wait for the load to stop.


}
