
#include <Wire.h>
#define RFSLAVE 8
void setup()
{
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  Serial.println ( "Master Ready" );
}

void loop()
{
  char c;
  Wire.requestFrom(RFSLAVE, 1);
  if(Wire.available())     // slave may send less than requested
  {
    c = Wire.read();       // receive a byte as character
    if (c)
      Serial.print(c);     // print the character 
    delay (1);  
  }
  
  if (Serial.available())
  {
     c = Serial.read();
     Wire.beginTransmission(8); // transmit to device
     Wire.write(c);             // sends bytes
     Wire.endTransmission();    // stop transmitting
     delay (20);
  }
}