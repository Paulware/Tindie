/*
 Example sketch for the Wiimote Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <Wii.h>
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//WII Wii(&Btd); // This will start inquiry which will connect to any Wiimote
WII Wii(&Btd,0x00,0x1E,0x35,0xD0,0x04,0x25); // This will connect to the Wiimote with that specific Bluetooth Address

bool printAngle;

void setup() {
  Serial.begin(115200);

  for (int i=0; i<4; i++)
    pinMode (i+4,OUTPUT);
  clearLEDs();
  digitalWrite (4,0);
  
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nWiimote Bluetooth Library Started"));
}

void clearLEDs()
{
  for (int i=0; i<4; i++)
    digitalWrite (i+4,1);
}
void loop() {
  Usb.Task();
  if(Wii.wiimoteConnected) {
    if(Wii.getButtonClick(HOME)) { // You can use getButtonPress to see if the button is held down
      Serial.print(F("\r\nHOME"));
      Wii.disconnect(); // If you disconnect you have to reset the Arduino to establish the connection again
    } 
    else {
      if(Wii.getButtonClick(LEFT)) {
        Wii.setAllOff();
        Wii.setLedOn(LED1);
        Serial.print(F("\r\nLeft"));
        clearLEDs();
        digitalWrite (4,0);
      }
      if(Wii.getButtonClick(RIGHT)) {
        Wii.setAllOff();
        Wii.setLedOn(LED3);
        Serial.print(F("\r\nRight"));
        clearLEDs();
        digitalWrite (6,0);
      }
      if(Wii.getButtonClick(DOWN)) {
        Wii.setAllOff();
        Wii.setLedOn(LED4);
        Serial.print(F("\r\nDown"));
        clearLEDs();
      }      
      if(Wii.getButtonClick(UP)) {
        Wii.setAllOff();
        Wii.setLedOn(LED2);          
        Serial.print(F("\r\nUp"));
        clearLEDs();
        digitalWrite (7,0);
      }

      if(Wii.getButtonClick(PLUS)) {
        Serial.print(F("\r\nPlus"));
      }      
      if(Wii.getButtonClick(MINUS)) {
        Serial.print(F("\r\nMinus"));
      }

      if(Wii.getButtonClick(ONE)) {
        Serial.print(F("\r\nOne"));
      }      
      if(Wii.getButtonClick(TWO)) {
        Serial.print(F("\r\nTwo"));
      }

      if(Wii.getButtonClick(A)) {
        printAngle = !printAngle;
        Serial.print(F("\r\nA"));
      }      
      if(Wii.getButtonClick(B)) {
        Wii.setRumbleToggle();
        Serial.print(F("\r\nB"));
      }
    }
    if(printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(Wii.getPitch());
      Serial.print(F("\tRoll: "));
      Serial.print(Wii.getRoll());
      if(Wii.nunchuckConnected) {
        Serial.print(F("\tNunchuck Pitch: "));
        Serial.print(Wii.getNunchuckPitch());
        Serial.print(F("\tNunchuck Roll: "));
        Serial.print(Wii.getNunchuckRoll());        
      }
    }
  }
  if(Wii.nunchuckConnected) {
    if(Wii.getButtonClick(Z))
      Serial.print(F("\r\nZ"));
    if(Wii.getButtonClick(C))
      Serial.print(F("\r\nC"));
    if(Wii.getAnalogHat(HatX) > 137 ||  Wii.getAnalogHat(HatX) < 117 || Wii.getAnalogHat(HatY) > 137 || Wii.getAnalogHat(HatY) < 117) {
      Serial.print(F("\r\nHatX: "));
      Serial.print(Wii.getAnalogHat(HatX));
      Serial.print(F("\tHatY: "));
      Serial.print(Wii.getAnalogHat(HatY));
    }
  }
}
