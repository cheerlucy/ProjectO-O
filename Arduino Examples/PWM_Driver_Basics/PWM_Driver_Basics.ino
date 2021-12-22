/* Project FOD-PWM driver (unidirection)
 * 
 * Connect any Arduino PWM capable PIN to the SW pin of the module, and the Arduino GND to the module GND, 
 * Then the load(fans, heating pads, etc.) can be drived to any INTENSITY(from 0 to 255, min to max) by analogWrite(PIN, INTENSITY);
 * 
 * The PINs definition of the module is similar to the three-wire interface (IN/OUT, 5V, GND) commonly used in the Arduino external sensing/output modules, 
 * but for the purpose of direct button control, the VIN voltage of Pin2 here is provided by the battery or other power supplies directly connected to the module.
 * Therefore, only SW and GND should be connected when using the Arduino to control the module, to avoid a reverse breakdown of the Arduino 
 * due to inconsistency with the on-chip power supply level of the Arduino.
 * 
 * The analogWrite() function uses PWM, so if you want to change the pin you're
   using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
   are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.
 * Reference: http://www.arduino.cc/en/Tutorial/Fade , the Fade example of Arduino.
 * 
 * Copyright (c) 2021 Anonymous for submission.
 * 
*/

int driver = 9;           // the PWM pin the driver SW pin is attached to
int intensity = 0;  
int steplength = 5;    
void setup() {
  // initialize the digital pin as an output.
  pinMode(driver, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(driver, intensity);

  // change the brightness for next time through the loop:
  intensity = intensity + steplength;

  // reverse the direction of the fading at the ends of the fade:
  if (intensity <= 0 || intensity >= 255) {
    steplength = -steplength;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
