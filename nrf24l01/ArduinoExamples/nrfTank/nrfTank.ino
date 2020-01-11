//  NRF24L01 truck or tank
#include <SendOnlySoftwareSerial.h>
#include <MemoryFree.h>
#include <EEPROM.h>

#define FULLSPEED 255
SendOnlySoftwareSerial turret (8); // RX (not used)

char testCharacters [] = {'-','-','-','-','+','+','+','+'};
int testIndex = 0;
unsigned long testTimeout = 0;
unsigned long offTimeout = 0;
unsigned long speedTimeout = 0;
int turnPower = 50;
int timeoutTime = 900;

byte health = 0;
unsigned long initPixelsTimeout = 0;
int state = 0;

void setup() {

  health = EEPROM.read(0);
  if ((health > 4) || (health < 0) ) {
     health = 4;
     EEPROM.write (0,4);
  }
  

  Serial.begin (9600);// Must be 9600 because receiver is same
  Serial.println ( "nrfTank Ready");

  turret.begin (115200);
  turret.write (health);

  Serial.print ( "Got an EEPROM health of: " );
  Serial.println ( health );
    
  pinMode (5, OUTPUT); 
  analogWrite (5, 0);

  pinMode (6, OUTPUT);
  analogWrite (6, 0);

  pinMode (9, OUTPUT);
  analogWrite (9, 0);

  pinMode (10, OUTPUT);
  analogWrite (10,0); 
     
  testTimeout = 1; // Not used currently

  speedTimeout = 1;

  initPixelsTimeout = millis() + 5000;
  Serial.println ( "Done in setup" );
}



void loop() {
  char ch;
  //int irDetected;  
  static char lastCh = ' ';
  static bool fire = false;
  
  if (Serial.available()) {
     ch = Serial.read();
     Serial.print (ch);
     if (ch == 'L')  { // Left Forward      
        analogWrite (6,0);
        analogWrite (5,FULLSPEED);
     } else if (ch == 'l')  { // Left Reverse   
        analogWrite (5,0);
        analogWrite (6,FULLSPEED);
     } else if (ch == 'R')  { // Right Forward
        analogWrite (10,0);
        analogWrite (9,FULLSPEED);
     } else if (ch == 'r')  { // Right Reverse
        analogWrite (9,0);
        analogWrite (10,FULLSPEED);
     } else if (ch == 'S') { // Left stop 
        analogWrite (6,0);
        analogWrite (5,0);
     } else if (ch == 's') { // Right stop 
        analogWrite (9,0);
        analogWrite (10,0);
     } else if (ch == 'T') { // turret left
        turret.write ( 'l' );  
     } else if (ch == 't') { // turret right 
        turret.write ( 'r') ;
     } else if (ch == 'u') { // turret stop 
        turret.write ( 'S' ); 
     } else if ((ch == 'D') || (ch == '!')) { // reset health
        turret.write ( '!' );
        EEPROM.write (0,4);        
     } else if (ch == 'F') {
        if (!fire) {
           turret.write ( 'f');
           Serial.println ( "Sending f to turret" );
        }
        fire = true;
     } else if (ch == 'f') {
        fire = false;
     }
  }


}
