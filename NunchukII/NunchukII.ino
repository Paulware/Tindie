#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 115200
unsigned long timeout = 0;

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  // D2 selects which nunchuk to read from 
  pinMode (2,OUTPUT);
  digitalWrite (2,1);
  
  Serial.begin(BAUDRATE);
  nunchuk.init();
  for (int i=0; i<4; i++)
  {
    pinMode (i+4, OUTPUT);
    digitalWrite(i+4,1);
  }
}

void loop()
{
  if (millis() > timeout)
  {
    timeout = millis() + 100;
    nunchuk.update();

    Serial.print(nunchuk.analogX, DEC);
    Serial.print(' ');
    Serial.print(nunchuk.analogY, DEC);
    Serial.print(' ');
    Serial.print(nunchuk.accelX, DEC);
    Serial.print(' ');
    Serial.print(nunchuk.accelY, DEC);
    Serial.print(' ');
    Serial.print(nunchuk.accelZ, DEC);
    Serial.print(' ');
    Serial.print(nunchuk.zButton, DEC);
    if (nunchuk.zButton)
      digitalWrite (4,0);
    else
      digitalWrite (4,1);
    
    if (nunchuk.cButton)
      digitalWrite ( 6,0);
    else
      digitalWrite ( 6,1); 
    
  
    Serial.print(' ');
    Serial.println(nunchuk.cButton, DEC);
  }  
}
