/*
   Connect this device to wireslave
   When you press reset on the wireslave
   you should see data on this serial monitor
*/
#include <Wire.h>
void setup()
{
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  Serial.println ( "Master Ready" );
}

void sendOne ( char ch )
{
   Wire.beginTransmission(3); // transmit to RGB
   Wire.write(ch);       // sends bytes
   Wire.endTransmission();    // stop transmitting
   delay (1);
}

void loop()
{
  char c;
  Wire.requestFrom(4, 1);     // request 1 byte from slave device #2
  if(Wire.available())    // slave may send less than requested
  {
    c = Wire.read(); // receive a byte as character
    if (c)
    {
      Serial.print(c);         // print the character 
      if (c == 'R') 
      {
        sendOne ('R' );
        sendOne ('b' );
        sendOne ('g' );        
        Serial.println ( "Rbg");
      }
      else if (c == 'G')
      {
        sendOne ( 'G');
        sendOne ( 'r' );
        sendOne ( 'b' );
        Serial.println ( "rbG" );
      }
      else if (c == 'B')
      {
        sendOne ( 'B');
        sendOne ( 'r' );
        sendOne ( 'g' );
        Serial.println ( "rBg" );
      }
      else if (c == 'O')
      {
        sendOne ( 'b' );
        sendOne ( 'r' );
        sendOne ( 'g' );
      }
    }  
    delay (1);  
  }
  
  if (Serial.available())
  {
     c = Serial.read();
     Wire.beginTransmission(3); // transmit to device #2
     Wire.write(c);       // sends bytes
     Wire.endTransmission();    // stop transmitting
     delay (20);    
  }  
}
