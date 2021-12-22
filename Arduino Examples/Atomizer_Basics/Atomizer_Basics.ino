/* Smello-Ultrasonic atomizer driver
 * Connect any Arduino digital PIN to the SW pin of the atomizer module, and the Arduino GND is connected to the module GND, 
 * Then the atomizer can be switched on/off by digitalWrite(PIN, HIGH/LOW)
 * 
 * The PINs definition of the module is similar to the three-wire interface (IN/OUT, 5V, GND) commonly used in the Arduino external sensing/output modules, 
 * but for the purpose of direct button control, the 5V voltage of Pin2 here is provided by the LDO on the module.
 * Therefore, only SW and GND should be connected when using the Arduino to control the module, to avoid a reverse breakdown of the Arduino 
 * due to inconsistency with the on-chip power supply level of the Arduino.
 * 
 * Copyright (c) 2021 Anonymous for submission.
 * 
*/

int atomizer = 13;

void setup() {
  // initialize the digital pin as an output.
  pinMode(atomizer, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(atomizer, HIGH);   // turn the atomizer on 
  delay(1000);               // wait for a second
  digitalWrite(atomizer, LOW);    // turn the atomizer off 
  delay(1000);               // wait for a second
}
