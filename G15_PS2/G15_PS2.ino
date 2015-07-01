/*
This is Arduino example sketch for G15 shield and Shield_PS2
The code is provided as it is. Cytron Technologies does not take
any responsibility to ensure the working of the sketch.
Please visit Shield-G15 and Shield-PS2 product page to get the library.
Product page:
  Cytron G15 Shield: http://www.cytron.com.my/p-shield-g15
  G15 Cube Servo: http://www.cytron.com.my/p-g15
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Ing Hui, Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies
*/

#include <SoftwareSerial.h>
#include <Cytron_G15Shield.h>
#include <Cytron_PS2Shield.h>
Cytron_PS2Shield ps2(2, 3); // SoftwareSerial: Rx and Tx pin
Cytron_G15Shield g15(0, 1, 9); // SoftwareSerial: Rx, Tx and Control pin. 
//Cytron_G15Shield g15(9); // HardwareSerial: Control pin. This is for REV.1 G15 Shield.

#define G15_1 1
#define G15_2 2
#define LED 13

void setup()
{
  g15.begin(19200); // G15 default baudrate
  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  ps2.reset(1);             //call to reset Shield-PS2
  delay(100);
  ps2.reset(0);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  delay(1000);
  g15.setWheelMode(G15_1); // Set G15 to wheel mode
  g15.setWheelMode(G15_2); // Set G15 to wheel mode
}

void loop()
{
 
  while(ps2.readButton(PS2_CONNECTION_STATUS) == 0);
  while(ps2.readButton(PS2_CONNECTION_STATUS) == 1){
  if((ps2.readButton(PS2_LEFT_1) == 0) || (ps2.readButton(PS2_LEFT_2) == 0) || (ps2.readButton(PS2_RIGHT_1) == 0) || (ps2.readButton(PS2_RIGHT_2) == 0)) 
  {
          g15.setLED(G15_1, ON);
          delay(10);
          g15.setLED(G15_1, OFF);
          delay(10);
  }
  else
  {
          g15.setLED(G15_2, ON);
          delay(10);
          g15.setLED(G15_2, OFF);
          delay(10);
  }  
  if(ps2.readButton(PS2_UP) == 0) // 0 = pressed, 1 = released
  {
    g15.setWheelSpeed(G15_1, 1023, CW); // Full speed with CW direction
    g15.setWheelSpeed(G15_2, 1023, CW); // Full speed with CW direction
  }
  else if(ps2.readButton(PS2_DOWN) == 0) // 0 = pressed, 1 = released
  {
    g15.setWheelSpeed(G15_1, 1023, CCW); // Full speed with CW direction
    g15.setWheelSpeed(G15_2, 1023, CCW); // Full speed with CW direction
  }
  else if(ps2.readButton(PS2_RIGHT) == 0) // 0 = pressed, 1 = released
  { 
    g15.setWheelSpeed(G15_1, 1023, CW); // Full speed with CW direction
    g15.setWheelSpeed(G15_2, 1023, CCW); // Full speed with CW direction 
  }
  else if(ps2.readButton(PS2_LEFT) == 0) // 0 = pressed, 1 = released
  {
    g15.setWheelSpeed(G15_1, 1023, CCW); // Full speed with CW direction
    g15.setWheelSpeed(G15_2, 1023, CW); // Full speed with CW direction
  }
  else
  {
    g15.setWheelSpeed(G15_1, 0, CCW); // Half speed with CCW direction
    g15.setWheelSpeed(G15_2, 0, CCW); // Half speed with CCW direction
  }
  }
}
