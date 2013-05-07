#define SLAVEADDRESS 3
#include <Wire.h>

int columns [] = {5,12,13,8,15,7,3,2};
int rows[] = {9,4,17,6,10,16,11,14};
byte bits[] = {1,2,4,8,0x10, 0x20, 0x40, 0x80};
unsigned long timeout = 0;
int x = 0;
int y = 0;

byte matrix[] = {0,0,0,0,0,0,0,0};

void showMatrix ( )
{
  for (int i=0; i<8; i++)
  {
    // Write column i
    digitalWrite (columns[i], 0);
    for (int j=0; j<8; j++)
    {
      if ((bits[j] & matrix[i]) > 0) 
        // setPin (i, j, true);
        digitalWrite ( rows[j], 1);
      else
        digitalWrite ( rows[j], 0);
        // setPin (i, j, false);
    }   
    delay (1); // Let the lights shine for a little while
    
    // Turn off all pins in the current column  
    digitalWrite (columns[i], 1);
    for (int j=0; j<8; j++)
      digitalWrite (rows[j], 0);
  }  
}

void clearAll ()
{
  for (int i=0; i<8; i++)
  {
    digitalWrite ( columns[i], 1);
  }  
}

// This function will 8 characters (1 for each row);
void receiveEvent(int howMany)
{
  char c;
  for (int i=0; i<howMany; i++)
  {
    if (howMany == 8)
    {
      c = Wire.read();
      matrix[i] = (byte) c;
    }    
  }
}

void setup()
{
  Wire.begin(SLAVEADDRESS);     // join i2c bus with slave Address
  Wire.onReceive(receiveEvent);  
  
  for (int i=0; i<18; i++)
    pinMode (i,OUTPUT);
  clearAll();
  timeout = millis() + 500;
}
/*
  Column must be set on (0)
  All row items should be 1 accept the item you want to set 
*/
void setDot ( int column, int row, bool offOn )
{
  if (offOn)
    matrix[column] |= bits [row];
  else
    matrix[column] &= ~bits[row];  
}
int p = 0;
int width = 2;
int showNow = 0;
void loop()
{
  showMatrix ();
}
