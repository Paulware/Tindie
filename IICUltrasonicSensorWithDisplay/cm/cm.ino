
#include <Wire.h>
unsigned long timeout = 0;
void setup()
{
  Serial.begin(9600);  // start serial for output
  Serial.println ( "Master Ready" );
  Wire.begin();         // join i2c bus (address optional for master)
  timeout = millis () + 500;
}

void loop()
{
  char c;
  float newValue = 0.0; 
  
  if (timeout)
    if (millis() > timeout)
    {
  
      Wire.requestFrom(2, 4);    // request 4 bytes from slave device #2
      while(Wire.available())    // slave may send less than requested
      {
        c = Wire.read(); // receive a byte as character
        newValue *= 10.0;
        newValue += c - '0'; 
        delay (1);	  
      }  
      newValue /= 10.0;
      Serial.print ( "newValue: " );
      Serial.println ( newValue);
      timeout = millis() + 500;
    }  
}
