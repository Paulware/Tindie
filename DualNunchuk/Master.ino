/*
   Connect this device to wireslave
   When you press reset on the wireslave
   you should see data on this serial monitor
*/
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <NunchukInfo.h>

NunStruct n[2] = {{0,0,false,false},{0,0,false,false}};
NunStruct last[2] = {{0,0,false,false},{0,0,false,false}};

void setup()
{
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  Serial.println ( "Reading Nunchuk at address 4" );
  Serial.println ( "w:[xxx,yyy] c z [XXX,YYY,ZZZ]" );
  Serial.println ( "  where w=id (0 or 1)" );
  Serial.println ( "  x = joystick x" );
  Serial.println ( "  y = joystick y" );
  Serial.println ( "  c = c button" );
  Serial.println ( "  z = z button" );
  Serial.println ( "  X = accelX" );
  Serial.println ( "  Y = accelY" );
  Serial.println ( "  Z = accelZ" );
}

unsigned long timeout = 0;
void showChuk (int id, struct NunStruct nunchuk)
{
  char msg [MAXNUNCHUKCHARS];
  NunchukInfo::writeChuk (id, nunchuk,msg);
  Serial.println ( msg );
}

void loop()
{
  char ch;
  int id = 0;
  
  if (millis() > timeout)
  {
    Wire.requestFrom(4, MAXNUNCHUKCHARS-1);  // request data from slave
    while(Wire.available())    // slave may send less than requested
    {
      ch = Wire.read(); // receive a byte as character
      Serial.print ( ch );
      // NunchukInfo::readChuk (id,n[id],ch );
    }
    Serial.println ( );
    // NunchukInfo::readChuk (id,n[id],0); // reset
    
    //if ( NunchukInfo::nunchukDelta ( n[id], last[id] ) ) 
    //  showChuk ( id, n[id] );
    timeout = millis() + 100;
  }

  /*  
  if (Serial.available())
  {
     c = Serial.read();
     Wire.beginTransmission(2); // transmit to device #2
     Wire.write(c);       // sends bytes
     Wire.endTransmission();    // stop transmitting
     delay (20);    
  }  
  */
}

