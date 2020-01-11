#include <SPI.h>
#include "RF24.h"

//nRF24 pins
// Cables are:
//     CE       ->  9
//     CSN      -> 10
//     MOSI     -> 11
//     MISO     -> 12
//     SCK      -> 13

//    A Button  ->  2
//    B Button  ->  3 
//    C Button  ->  4
//    D Button  ->  5
// Fire Button  ->  6

#define CEPIN 9
#define CSNPIN 10
#define TXLENGTH 32

String leftSide = "stop";
String rightSide = "stop";
String fire = "stop";
String turret = "stop";
String dButton = "stop";
String cButton = "stop";
int buttons[] = {2,3,4,5,6};
RF24 radio(CEPIN,CSNPIN); 
char payload [TXLENGTH]; 

int readValue (bool init=false) {
  static int lastValue = -1;
  int pins[] = {8,A4,7,A5};
  int values[] = {1,2,4,8};
  int total = 0;

  if (init) {
     for (int i=0; i<4; i++) {
       pinMode (pins[i], INPUT);
       digitalWrite (pins[i], 1);    
     }
  }
  for (int i=0; i<4; i++) {
    if (digitalRead (pins[i]) == 0) {
      total = total + values[i];        
    }
  }
  if (total != lastValue) {
    Serial.print ( "Total: ");
    Serial.println ( total );
    lastValue = total;
  }
  return total;
}

void initializeRadio(int chan) {
  int newChannel = 0x24 + (chan * 8);
  const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'}; 
  radio.begin();
  radio.setAddressWidth(5);
  newChannel = 0x2c;
  Serial.print ( "Radio tx on channel: " );
  Serial.println ( newChannel,HEX );
  
  radio.setChannel(0x20 + (chan * 8));
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize (TXLENGTH);
  radio.setPALevel (3);
  radio.setAutoAck(0);
  radio.openWritingPipe(thisSlaveAddress);  
  radio.stopListening();    
}

void setup() {
  Serial.begin (9600);
  Serial.println ("nRFJoyStick");
  initializeRadio (1); // readValue(true));

  for (int i=0; i<5; i++) {
    pinMode (buttons[i],INPUT);
    digitalWrite (buttons[i], 1);
  }
}

void readJoystick() {
  int pins[] = {A1, A3};
  static int lastValues[] = {1,1};
  char returnValues [][3] = {{'l','S','L'},{'r','s','R'}};
  int value;
  int val;
  char returnValue = 0;
  int numJoysticks = 2;
  for (int i=0; i<numJoysticks; i++) {
     value = analogRead ( pins[i] );
     val = 1;
     if (value > 700) {
        val = 0;
     } else if (value < 200) {
        val = 2;
     }

     if (val != lastValues[i] ) {
        lastValues[i] = val;
        returnValue = returnValues [i][val];
        break;
     }
  }

  switch (returnValue) {
    case 0:
      break;
    case 'L':
      leftSide = "forward";
      break;
    case 'l':
      leftSide = "reverse";
      break;
    case 'S':
      leftSide = "stop";
      break;
    case 'R':
      rightSide = "forward";
      break;
    case 'r':
      rightSide = "reverse";
      break;
    case 's':
      rightSide = "stop";
      break;
    default:
      break;
  }
    
}

void readButtons () {
  static int lastValues[] = {1,1,1,1,1};
  char pressValues[] = {'T','t','C','D','F'};
  char releaseValues[] = {'u', 'u', 'c', 'd','f'};
  char value = 0;

  for (int i=0; i<5; i++) {
     value = digitalRead (buttons[i]);
     if (value != lastValues[i]) {
        lastValues[i] = value;
        if (value == 0) {
           value = pressValues[i];
           break; 
        } else { 
           value = releaseValues[i];
           break;
        }
     }
  }

  switch (value) {
    case 0:
      break;
    case 'C':
      cButton = "press";
      break;
    case 'c':
      cButton = "release";
      break;
    case 'D':
      dButton = "press";
      break;
    case 'd':
      dButton = "release";
      break;      
    case 'T':
      turret = "forward";
      break;
    case 't':
      turret = "reverse";
      break;
    case 'u':
      turret = "stop";
      break;
    case 'F':
      fire = "fire";
      break;
    case 'f':
      fire = "frelease";
      break;
    default:
      break;
  }  
}

void tx () {
  bool rslt;
  char ch;

  if (leftSide == "forward") {
    ch = 'L';      
  } else if (leftSide == "reverse") {
    ch = 'l';
  } else { 
    ch = 'S';
  }     
  payload[0] = ch;
  
  if (rightSide == "forward") {
    ch = 'R';      
  } else if (rightSide == "reverse") {
    ch = 'r';
  } else { 
    ch = 's';
  } 
  payload[1] = ch;

  if (turret == "forward") {
    ch = 'T';
  } else if  (turret == "reverse") {
    ch = 't';
  } else {
    ch = 'u';
  }
  payload[2] = ch;

  if (fire == "fire") {
    ch = 'F';
  } else {
    ch = 'f';
  }
  payload[3] = ch;


  if (cButton == "press") {
    ch = 'C';
  } else {
    ch = 'c';
  }
  payload[4] = ch;  

  if (dButton == "press") {
    ch = 'D';
  } else {
    ch = 'd';
  }
  payload[5] = ch;  
  
  rslt = radio.write (&payload[0], TXLENGTH);
  if (!rslt) {
    Serial.println ( "ERROR in tx" );
  }
}

void showLastState() {
  static int state = 0;
  char ch=0;
  int val;
  bool rslt;
   
  state = state + 1;
  state = state % 3;
  switch (state) {
    case 0: 
       if (leftSide == "forward") {
          ch = 'L';      
       } else if (leftSide == "reverse") {
          ch = 'l';
       } else { 
          ch = 'S';
       }
    break;
    
    case 1:
       if (rightSide == "forward") {
          ch = 'R';      
       } else if (rightSide == "reverse") {
          ch = 'r';
       } else { 
          ch = 's';
       }
    break;
    case 2:
       if (turret == "forward") {
         ch = 'T';
       } else if (turret == "reverse") {
         ch = 't';
       } else {
         ch = 'u';
       }
    break;
  }
  //if (ch != 0) { 
  //  tx(ch);
  //}   
}

void loop() {
  static int count = 0;
  bool rslt;
  char ch;
  static unsigned long timeout = 0;
  if (millis() > timeout) { 
      timeout = millis() + 50;
      readButtons();
      readJoystick();
      tx();
  }
}
