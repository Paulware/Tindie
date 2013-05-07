/*
   Connect this device to wireslave
   When you press reset on the wireslave
   you should see data on this serial monitor
*/
#include <Wire.h>
#define NUMICONS 4
int which = 0;
unsigned long timeout = 0;
char icons[NUMICONS][8] = {
                            {0x3c, 0x3c, 0x3c, 0x3c, 0xff, 0x7e, 0x3c, 0x18},
                            {0x08, 0x0c, 0xfe, 0xff, 0xff, 0xfe, 0x0c, 0x08},
                            {0x18, 0x3c, 0x7e, 0xff, 0x3c, 0x3c, 0x3c, 0x3c}, 
                            {0x10, 0x30, 0x7f, 0xff, 0xff, 0x7f, 0x30, 0x10},
                             
                           };
void setup()
{
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  Serial.println ( "Master Ready" );
}

void sendMatrix (int whichIcon)
{
  Wire.beginTransmission(3); // transmit to device #3
  for (int i=0; i<8; i++)
    Wire.write ( icons[whichIcon][i] );
  Wire.endTransmission();    // stop transmitting
  delay (20);    
}

void loop()
{
  if (millis() > timeout)
  {
    sendMatrix ( which );
    which ++;
    which %= NUMICONS;
    timeout = millis () + 1000;
  }
}
