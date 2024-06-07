/*!
    Relays usage example for Sequent Microsystems Home Automation HAT
    -->https://sequentmicrosystems.com/collections/all-io-cards/products/raspberry-pi-home-automation-card
    Requirments: Any arduino card with I2C, Sixteen Analog/Digital Inputs HAT from Sequent Microsystems

    Method 1:
      Connect I2C bus, 5V and GND from Arduino card to Sixteen Analog/Digital Inputs hat, pin map below
     SIGNAL  CONNECTOR    SIGNAL\n
      ---------------------------
           -- 1|O O| 2--  +5V
   I2C SDA -- 3|O O| 4--  +5V
   I2C SCL -- 5|O O| 6--  GND
           -- 7|O O| 8--
       GND -- 9|O O|10--
           --11|O O|12--
           --13|O O|14--  GND
           --15|O O|16--
           --17|O O|18--
           --19|O O|20--  GND
           --21|O O|22--
           --23|O O|24--
       GND --25|O O|26--
           --27|O O|28--
           --29|O O|30--  GND
           --31|O O|32--
           --33|O O|34--  GND
           --35|O O|36--
           --37|O O|38--
       GND --39|O O|40--

    Method 2:
    Use sequent Microsystems Uno, Nano, Teensy,Feather, ESP32 Raspberry Pi Replacement Kit with prefered arduino processor
    -->https://sequentmicrosystems.com/collections/accessories/products/raspberry-pi-replacement-card

    Method 3:
     Use Sequent Microsysstems ESP32 Pi replacement connected directly with the Home Automation card.
     Set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1
*/

#include "SM_16UNIVIN.h"

SM_16_UNIVIN card(0);// Sixteen Universal Inputs HAT with stack level 0 (no jumpers installed)

void setup() {
  Serial.begin(115200);
  delay(2000);

  if (card.begin() ) {
    Serial.print("Sixteen Universal Inputs Card detected\n");
  }
  else {
    Serial.print("Sixteen Universal Inputs Card NOT detected!\n");
  }
}


void loop() {
  if (card.isAlive())
  {
    for (int i = 1; i < 17; i++)
    {
      card.writeLED(i, 1);
      delay(250);
    }
    for (int i = 1; i < 17; i++)
    {
      card.writeLED(i, 0);
      delay(250);
    }
    delay(1000);
  }
}
