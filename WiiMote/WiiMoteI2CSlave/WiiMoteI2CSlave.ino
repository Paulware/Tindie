/*
 Example sketch for the Wiimote Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <Wii.h>
#include <Wire.h>
// I2C Address
#define SLAVEADDRESS 2
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//WII Wii(&Btd); // This will start inquiry which will connect to any Wiimote
WII Wii(&Btd,0x00,0x1E,0x35,0xD0,0x04,0x25); // This will connect to the Wiimote with that specific Bluetooth Address

bool printAngle;
int tankNumber = 0;
char lastCommand = 0;
unsigned long timeout=0;

void setup() {
  Serial.begin(115200);

  for (int i=0; i<4; i++)
    pinMode (i+2,OUTPUT);
  clearLEDs();
  digitalWrite (3,0);
  
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nWiimote Bluetooth Library Started"));
  Wire.begin(SLAVEADDRESS);
  Wire.onRequest (requestEvent);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  char oneCh [] = " ";
  oneCh[0] = lastCommand;  
  Wire.write(oneCh);
  lastCommand = 0;
}

void clearLEDs()
{
  for (int i=0; i<4; i++)
    digitalWrite (i+2,1);
}
void loop() {
  Usb.Task();
  if(Wii.wiimoteConnected) {    
    // You can use getButtonPress to see if the button is held down
    if(Wii.getButtonClick(HOME) || (Wii.getButtonPress(HOME) && (millis() > timeout))) { 
      Serial.print(F("\r\nHOME"));
      lastCommand = 'H';
      // Wii.disconnect(); // If you disconnect you have to reset the Arduino to establish the connection again
      timeout = millis() + 333; // Check 3 times a second
    } 
    else {      
      if(Wii.getButtonClick(LEFT)|| (Wii.getButtonPress(LEFT) && (millis() > timeout))) {
        Wii.setAllOff();
        Wii.setLedOn(LED1);
        Serial.print(F("\r\nLeft"));
        clearLEDs();
        digitalWrite (2,0);
        lastCommand = 'L';
        timeout = millis() + 333; // Check 3 times a second
      }
      if(Wii.getButtonClick(RIGHT)|| (Wii.getButtonPress(RIGHT) && (millis() > timeout))) {
        Wii.setAllOff();
        Wii.setLedOn(LED3);
        Serial.print(F("\r\nRight"));
        clearLEDs();
        digitalWrite (4,0);
        lastCommand = 'R';
        timeout = millis() + 333; // Check 3 times a second
      }
      if(Wii.getButtonClick(DOWN)|| (Wii.getButtonPress(DOWN) && (millis() > timeout))) {
        Wii.setAllOff();
        Wii.setLedOn(LED4);
        Serial.print(F("\r\nDown"));
        clearLEDs();
        lastCommand = 'R';
        timeout = millis() + 333; // Check 3 times a second
      }      
      if(Wii.getButtonClick(UP)|| (Wii.getButtonPress(UP) && (millis() > timeout))) {
        Wii.setAllOff();
        Wii.setLedOn(LED2);          
        Serial.print(F("\r\nUp"));
        clearLEDs();
        digitalWrite (5,0);
        lastCommand = 'G';
        timeout = millis() + 333; // Check 3 times a second
      }

      if(Wii.getButtonClick(PLUS)) {
        Serial.print(F("\r\nPlus"));
        tankNumber ++;
        tankNumber %= 10;
        lastCommand = '0' + tankNumber;
        timeout = millis() + 333; // Check 3 times a second
      }      
      if(Wii.getButtonClick(MINUS)) {
        Serial.print(F("\r\nMinus"));
        tankNumber --;
        if (tankNumber == -1)
          tankNumber = 9;
        lastCommand = '0' + tankNumber;
        timeout = millis() + 333; // Check 3 times a second
      }
      
      if(Wii.getButtonClick(ONE)|| (Wii.getButtonPress(ONE) && (millis() > timeout))) {
        Serial.print(F("\r\nOne"));
        timeout = millis() + 333; // Check 3 times a second
      }      
      if(Wii.getButtonClick(TWO)|| (Wii.getButtonPress(TWO) && (millis() > timeout))) {
        Serial.print(F("\r\nTwo"));
        timeout = millis() + 333; // Check 3 times a second
      }

      if(Wii.getButtonClick(A)|| (Wii.getButtonPress(A) && (millis() > timeout))) {
        // printAngle = !printAngle;
        Serial.print(F("\r\nA"));
        lastCommand = 'F';
        timeout = millis() + 333; // Check 3 times a second
      }      
      if(Wii.getButtonClick(B)|| (Wii.getButtonPress(B) && (millis() > timeout))) {
        // Wii.setRumbleToggle();
        Serial.print(F("\r\nB"));
        lastCommand = 't';
        timeout = millis() + 333; // Check 3 times a second
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
