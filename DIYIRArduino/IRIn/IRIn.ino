#include <TimerOne.h>
#include <IR.h>

#define INPUTPIN 10
IR IRReceiver (INPUTPIN);

void callback()
{
  IRReceiver.callback();
}

void setup()
{
  Serial.begin (115200);
  Timer1.initialize(50); // 50 microsecond task
  Timer1.attachInterrupt(callback,0);  
 
  Serial.println ( "Ready to receive an IR pulse" );
}

char decodePulse (int value) 
{
  char ch = 0;
  int sonyNumbers[] = {0x1910,0x1010,0x1810,0x1410,0x1c10,0x1210,0x1a10,0x1610,0x1e10,0x1110};
  for (int i=0; i<10; i++)
    if (value == sonyNumbers[i])
      ch = '0' + i;

  if (value && !ch) 
  { 
      Serial.print ( "Received this raw pulse: " );
      Serial.println ( value, HEX );
  }
  return ch;
}

void loop()
{
  int val;
  char ch;
 
  if (IRReceiver.irReady)
  {
    val = IRReceiver.decodeBits (15, true, false);    
    ch = decodePulse (val);
    if (ch)
    {
      Serial.print ( "Sony IR: " );
      Serial.println (ch);
    }  
    IRReceiver.resetIR(); 
  }  



}

