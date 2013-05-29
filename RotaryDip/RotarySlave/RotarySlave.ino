#include <Wire.h>

#define BAUDRATE 115200
#define LOWPIN 2
#define HIPIN 13
// This device is on IIC slave address 6
#define SLAVEADDRESS 6
// #define DEBUGIT

int pins;
void setup()
{
  #ifdef DEBUGIT
  Serial.begin(BAUDRATE);
  Serial.print ( "Rotary Dip ready Slave Address = " );
  Serial.println ( SLAVEADDRESS );
  #endif
  Wire.begin(SLAVEADDRESS);     // join i2c bus
  Wire.onRequest(requestEvent); // register event
  for (int i=HIPIN; i>(LOWPIN-1); i--)
  {
    pinMode (i, INPUT);
    digitalWrite(i,1); // set pull-up resistor
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  int p = pins;
  char threeCh [] = "000";
  
  threeCh[0] = (p/100) + '0'; 
  p = p - ((p/100)*100);  
  threeCh[1] = (p/10) + '0'; 
  p = p - ((p/10)*10);  
  threeCh[2] = (p%10) + '0'; 
  Wire.write (threeCh);
}


int readPins()
{
  int values[] = {0,0,2,4,8,1,40,20,10,80, 400, 200, 100, 800};
  int value = 0;     
    
  for (int i=HIPIN; i>(LOWPIN-1); i--)
    if (!digitalRead (i))
      value += values[i];
  return value;
}

void loop()
{
  static int lastPins = 0;
  pins = readPins();
  #ifdef DEBUGIT
  if (pins != lastPins)
  {
    Serial.print ( "pins: " );
    Serial.println ( pins);
  }
  #endif
  lastPins = pins;
  delay (100);
}
