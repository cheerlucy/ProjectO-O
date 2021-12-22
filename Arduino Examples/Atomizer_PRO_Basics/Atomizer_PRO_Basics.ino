/* Project FOD-Ultrasonic atomizer driver (PRO Version)
 * NOTICE: 
 *   Before powering on, one of the pins representing Pro (Program) and Man (Manual) modes must be shorted by the jumper cap, 
 *   otherwise the power IC may not work properly or even be burned.
 * Program mode:
 *   The use of arduino control requires first to jumper the two pins below the 'Pro' and connect the five pins on the left to the appropriate pins of the Arduino, 
 *   where the SW and GND pins are used to control the switch in accordance with the Basic version.
 *   CS DI SCK is based on the three-line SPI protocol to control the voltage supply to the atomizer so as to adjust the amount of fog in real time.
 *   For Uno: (Pins should be changed according to the arduino model)
 *    CS - to digital pin 10  (SS pin)
 *    DI - to digital pin 11 (MOSI pin)
 *    SCK - to digital pin 13 (SCK pin)
 *   For Leonardo：
 *    CS - D10 (SS pin)
 *    DI - ICSP MOSI pin 
 *    SCK - ICSP SCK pin  
 *   when usb jack on the top
 *   2*3 ICSP:  x SCK  x 
 *              x MOSI x
 *   For Pro Micro:          
 *    CS - D10, DI - D16, SCK - D15
 * Manual mode:
 *   The module supports direct manual control without external programming by jumpering the two pins above the 'Man' to select Manual mode.
 *   Connect a button module to the left GND SW 5V pins to realize switch control.
 *   Connect a 10K ohm rheostat or rheostat module to the RL and RW pins (note that one pin should be connected to the tap end of the rheostat).
 *   Then the amount of fog can be controlled by screwing potentiometer. 
 *NOTICE:100K ohm potentiometers are not common, so the pro module are changed to use a 10K ohm potentiometers, 
 *       and the corresponding digital potentiometers can only be used in 0-10K range for current version hardware.
 * Thanks to Heather Dewey-Hagborg and Tom Igoe for the DigitalPotControl example.
 * 
 * Copyright (c) 2021 Anonymous for submission.
 * 
*/
// TO adjust the fogging speed, include the SPI library:
#include <SPI.h>
//
void fogSpeedControl(int value); //value range (0-25) 
// Connect Any digital pin to CS(here pin 10 as example, as the slave select for the digital pot in the module:
const int slaveSelectPin = 10;
int atomizer = 12; //atomizer switch: assign it to HIGH to make the atomizer start working, or the fogSpeedControl won't work.
void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  pinMode(atomizer, OUTPUT);
  digitalWrite (slaveSelectPin, HIGH);
  // initialize SPI:
  SPI.begin();
  fogSpeedControl(12); 
}

void loop() {
  
  // change the fogging speed from min to max:
 
    digitalWrite(atomizer, HIGH);
    fogSpeedControl(0);
    delay(500);
    digitalWrite(atomizer, LOW); // to prevent the chips(mosfet and inductor) overheat
    delay(2000);
    
    digitalWrite(atomizer, HIGH);
    fogSpeedControl(12);
    delay(500);
    digitalWrite(atomizer, LOW); // to prevent the chips(mosfet and inductor) overheat
    delay(2000);
    
    digitalWrite(atomizer, HIGH);
    fogSpeedControl(25);
    delay(500);
    digitalWrite(atomizer, LOW); // to prevent the chips(mosfet and inductor) overheat
    delay(2000);
  
}

void fogSpeedControl(int value) {
  // gain control of the SPI port
  // and configure settings
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));  //UNFINISHED. NEED TO BE TESTED.   by kilo --21.8.13
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI:
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH);
  // release control of the SPI port
  SPI.endTransaction();
}
