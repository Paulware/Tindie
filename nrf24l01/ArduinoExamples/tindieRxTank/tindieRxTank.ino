// This module gets loaded on the nrf/arduino component
// The NrfSerial class is used by the master device to drive
// this nrf component.
#include <EEPROM.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define CHANNEL 0x34

//nRF24 pins
#define CEPIN 9
#define CSNPIN 10
//     MOSI     -> 11
//     MISO     -> 12
//     SCK      -> 13


#define TXLENGTH 32
RF24 radio(CEPIN, CSNPIN);
char fire = 'f';
char dButton = 'd';
char cButton = 'c';

char payload[TXLENGTH];

void initializeRadio() {
  const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};
  
  radio.begin();
  radio.setAddressWidth(5);
  radio.setChannel(CHANNEL);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize (TXLENGTH);
  radio.setPALevel (3);
  radio.setAutoAck(0);
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
}

void setup() {
  Serial.begin (9600);
  initializeRadio ();
  Serial.print ( "!" );

  
  //LED
  pinMode (6,OUTPUT);
  digitalWrite (6,1);
  pinMode (7,OUTPUT);
  digitalWrite (7,1);
  pinMode (8,OUTPUT); // BLUE
  digitalWrite (8,0);  
  
}

void loop() {
  char ch;
  char oneCh[] = " ";
  unsigned char length;
  static unsigned long timeout = 0;
  static int count = 0;

  if (millis() > timeout) { 
    timeout = millis() + 50;
    if (radio.available()) {
      radio.read(&payload[0], TXLENGTH);
      ch = payload[0];
      if ((ch == 'L') || (ch == 'l')) { 
        Serial.print (ch);
      }
      
      ch = payload[1];      
      if ((ch == 'R') || (ch == 'r'))  {
        Serial.print (ch);
      }

      ch = payload[2];
      if ((ch == 'T') || (ch == 't')) {
        Serial.print (ch);
      }

      // One shot 
      ch = payload[3];
      if (ch == 'F') {
         if (fire == 'f') { 
            Serial.println ( "F" );
         } 
      }
      fire = ch;

      // Show on depress/release only once 
      ch = payload[4];
      if (ch == 'C')  {
         if (cButton == 'c' ) { 
           Serial.println ( "C" );
         }
      } else if (ch == 'c') {
         if (cButton == 'C') { 
            Serial.println ( "c" );
         }
      }
      cButton = ch;
      

      ch = payload[5];
      if (ch == 'D') {
         if (dButton == 'd' ) { 
           Serial.println ( "D" );
         }
      } else if (ch == 'd') {
         if (dButton == 'D') { 
            Serial.println ( "d" );
         }
      }
      dButton = ch;
      
      digitalWrite (8,1);
      digitalWrite (6,1);
      digitalWrite (7,0);   // GREEN
      
    } else {
      digitalWrite (7,1);
      digitalWrite (6,0); // RED    
    }
  }
}
