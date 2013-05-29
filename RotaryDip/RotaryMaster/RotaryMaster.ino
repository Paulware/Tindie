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

int readRotarySlave(bool &ready)
{
  static unsigned long timeout = 0;
  char c;
  int value = 0;
  ready = false;
  if (millis() > timeout)
  {
    ready = true;
    Wire.requestFrom(6, 3);     // request 3 byte from slave device #2
    delay (1);
    while(Wire.available())    // slave may send less than requested
    {
      c = Wire.read(); // receive a byte as character
      value = value * 10;
      value = value + c - '0';
      if (c)
        Serial.print(c);         // print the character 
      delay (1);  
    }
    Serial.println ();
    timeout = millis() + 1000;
  }
  return value;
}

void loop()
{
  static int lastRotary = 0;
  bool ready;
  int value = readRotarySlave(ready);
  if (ready)
  {
    if (value != lastRotary)
    {
      Serial.println ( value );
    }
    lastRotary = value;
  }
  
}

