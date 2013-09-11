#include "NunchukInfo.h"
#include "Arduino.h"

bool NunchukInfo::nunchukDelta ( ArduinoNunchuk nunchuk, struct NunStruct & last )
{
  bool changed = false;
  
  if (
      (abs(nunchuk.analogX - last.x) > 10) ||
      (abs(nunchuk.analogY - last.y) > 10) ||
      (abs(nunchuk.accelX - last.accelX) > 10) ||
      (abs(nunchuk.accelY - last.accelY) > 10) ||
      (abs(nunchuk.accelZ - last.accelZ) > 10) ||
      (nunchuk.cButton != last.cButton) ||
      (nunchuk.zButton != last.zButton)
     )
     {   
       last.x  = nunchuk.analogX;
       last.y  = nunchuk.analogY;
       last.cButton = nunchuk.cButton;
       last.zButton = nunchuk.zButton;       
       last.accelX = nunchuk.accelX;
       last.accelY = nunchuk.accelY;
       last.accelZ = nunchuk.accelZ;
       changed = true;
     }
  return changed;
}

bool NunchukInfo::nunchukDelta ( struct NunStruct nunchuk, struct NunStruct & last )
{
  bool changed = false;
  
  if (
      (abs(nunchuk.x - last.x) > 10) ||
      (abs(nunchuk.y - last.y) > 10) ||
      (abs(nunchuk.accelX - last.accelX) > 10) ||
      (abs(nunchuk.accelY - last.accelY) > 10) ||
      (abs(nunchuk.accelZ - last.accelZ) > 10) ||
      (nunchuk.cButton != last.cButton) ||
      (nunchuk.zButton != last.zButton)
     )
     {   
       last.x  = nunchuk.x;
       last.y  = nunchuk.y;
       last.cButton = nunchuk.cButton;
       last.zButton = nunchuk.zButton;       
       last.accelX = nunchuk.accelX;
       last.accelY = nunchuk.accelY;
       last.accelZ = nunchuk.accelZ;
       changed = true;
     }
  return changed;
}


void NunchukInfo::writeNum ( int num, char * str )
{
   int value;
   if (num > 999) 
     num = 999;
   value = num / 100;
   str[0] = '0' + value;   
   num = num - (value * 100);
   value = num / 10;
   str[1] = '0' + value;
   num = num - (value * 10);
   str[2] = '0' + num;
}

/* 
   write nunchuk data to a string 
*/
void NunchukInfo::writeChuk (int id, struct NunStruct nunchuk,
                             char * str)
{ //                       1         2
  //             01234567890123456789012345678
  strcpy ( str, "0:[xxx,yyy] 0 0 [xxx,yyy,zzz]" );
  str[0] = '0' + id;
  if (nunchuk.x <= 255)
    writeNum (nunchuk.x, &str[3]);
  if (nunchuk.y <= 255)
    writeNum (nunchuk.y, &str[7]);
  if (nunchuk.cButton)
     str[12] = '1';
  if (nunchuk.zButton)  
     str[14] = '1';     
  writeNum (nunchuk.accelX, &str[17]);
  writeNum (nunchuk.accelY, &str[21]);
  writeNum (nunchuk.accelZ, &str[25]);     
}

/*
   Read nunchuk data from a string 
*/
// 0:[xxx,yyy] 0 0 [xxx,yyy,zzz]
void NunchukInfo::readChuk(int & id, NunStruct & n, char ch)
{
  static int state = 0;
  static int intValue;
  static int count = 0;
  static NunStruct value;
  
  if (!ch) // reset
    state = 1;
  else 
  {
    count++;
    switch (state)
    {
      case 0: // sync on linefeed
        intValue = 0;
        if ((ch == 10) || (ch == ']')) // linefeed
          state = 1;
        count = 0;
      break;
          
      case 1: // get the nunchuk id
        if (ch == '[')
          state = 2;
        else if (ch == ':')
        {
          // ignore
        }        
        else if (ch == '1') 
        {
          count = 1;
          id = 1;
        }  
        else if (ch == '0')
        {
          id = 0;        
          count = 1;
        }  
        break;
                
      case 2: // get x
        if (ch == ',') 
        { // Done with the x value
           state = 3;
           value.x = intValue;
           intValue = 0;
        }
        else if ((ch >= '0') && (ch <= '9'))
        {
          intValue = (intValue * 10) + (ch - '0'); 
        }
        break;
      
      case 3: // Get y
        if (ch == ' ') // Done with y value
        {
          state = 4;
          value.y = intValue;
        }
        else if (ch == ']')
        {
          // ignore it
        }
        else if ((ch >= '0') && (ch <= '9'))
        {
          intValue = (intValue * 10) + (ch - '0'); 
        }  
        break;
        
      case 4: // get cbutton
        if (ch == ' ')
        {
          state = 5;
          value.cButton = intValue;
        }  
        else if (ch == '1') 
          intValue = 1;
        else if (ch == '0')
          intValue = 0;
      break;  
      
      case 5: // get zbutton
        if (ch == '[')
        {
          state = 6;
          value.zButton = intValue;
          intValue = 0;
        }  
        else if (ch == ' ') 
        {
          // ignore it
        }  
        else if (ch == '1') 
          intValue = 1;
        else if (ch == '0')
          intValue = 0;
      break;      
      
      case 6: // get the accelX
        if (ch == ',')
        {
           state = 7;
           value.accelX = intValue;
           intValue = 0;
        }
        else if ((ch >= '0') && (ch <= '9'))
          intValue = (intValue * 10) + (ch - '0');
      break;
      case 7: // get the accelY
        if (ch == ',')
        {
           state = 8;
           value.accelY = intValue;
           intValue = 0;
        }
        else if ((ch >= '0') && (ch <= '9'))
          intValue = (intValue * 10) + (ch - '0'); 
      break;
      case 8: // get the accelZ
        if (ch ==']')
        {
          state = 1;
          value.accelZ = intValue;
          if (count == 29) // correct
            n = value;
          intValue = 0;
        }
        else if ((ch >= '0') && (ch <= '9'))
          intValue = (intValue * 10) + (ch - '0'); 
      break;
    } // end switch      
  }  
}
