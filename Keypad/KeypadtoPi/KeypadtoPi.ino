
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 6, 7, 14, 15 };
// Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
byte colPins[COLS] = { 2, 3, 4, 5 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

byte outPins[] = {11,10,9,8};

void setup()
{
  Serial.begin(115200);
  Serial.println ( "Start keypad demo");

  for (int i=0; i<4; i++)
  {
    pinMode (outPins[i], OUTPUT);
    digitalWrite (outPins[i], 0);
  }
}


void keyTo4Pins (char key )
{
  for (int i=0; i<4; i++)
  {
    digitalWrite ( outPins[i], key % 2 );
    key = key / 2;    
  }
}

/*
  key   value
   0    1111
   A    1010
   B    1011
   C    1100
   D    1101
   *    1011
   #    1100
   1    0001
   2    0010
   3    0011
   4    0100
   5    0101
   6    0110
   7    0111
   8    1000
   9    1001
   
*/
void loop()
{
    
  char key = kpd.getKey();
  if(key)  // same as if(key != NO_KEY)
  {
    delay (200);
    Serial.println ( key);
    switch (key)
    {
      case '0':
        keyTo4Pins (15);
      break;
      
      case 'A':
      case 'B':
      case 'C':
      case 'D':
        keyTo4Pins ( key - 'A' + 10 );
        break;
      
      default:
        keyTo4Pins (key - '0');
        break;
        
      case '*':
        keyTo4Pins (11);
        break;
        
      case '#':
        keyTo4Pins (12);
        break;
    }
  }
}

