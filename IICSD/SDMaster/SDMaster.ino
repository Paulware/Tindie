/*
   Connect this device to wireslave
   When you press reset on the wireslave
   you should see data on this serial monitor
*/
#include <Wire.h>
#define SLAVESD 7
bool ready = false;
void setup()
{
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println ( "Master Ready" );
  delay (2000); // Let slave devices power up
  // Request a file:
  Wire.beginTransmission(SLAVESD); // transmit to device #2
  Wire.write("Script.txt");       // sends bytes
  Wire.endTransmission();         // stop transmitting
  ready = true;
}


void loop()
{
  char c;
  static unsigned long timeout = 1;
  static bool done = false;
  bool lineRead = false;
  bool allDone = false;
  if (timeout && ready)
    if (millis() > timeout)
    {
      Wire.requestFrom(7, 255);     // request 1 byte from slave device you will get many
      Serial.print ("got line from slave:");
      while(Wire.available())    // slave may send less than requested
      {
        c = Wire.read(); // receive a byte as character
        if (c==-1)
        {
          allDone = true;
          Serial.println( "Got the alldone signal from slave" );
          timeout = 0;
          break;
        }  
        else 
        {
          if (c)
            Serial.print((int) c);         // print the character 
          delay (1);  
          lineRead = true;
        }  
      }
      if (!allDone)
        timeout = millis() + 100;
    }  
  
  
  if (Serial.available())
  {
     c = Serial.read();
     Wire.beginTransmission(2); // transmit to device #2
     Wire.write(c);       // sends bytes
     Wire.endTransmission();    // stop transmitting
     delay (20);    
  }  
}
