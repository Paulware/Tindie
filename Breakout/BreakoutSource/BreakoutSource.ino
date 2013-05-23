#include <Wire.h>
#include <ArduinoNunchuk.h>
int columns [] = {5,12,13,8,15,7,3,2};
int rows[] = {9,4,17,6,10,16,11,14};
byte bits[] = {1,2,4,8,0x10, 0x20, 0x40, 0x80};
unsigned long timeout = 0;
int x = 0;
int y = 0;
int p = 0;
int width = 2;
int showNow = 0;
bool ballMissed = true;
int ballCount = 0;

// Ball offsets
int xOffset = 1;
int yOffset = 0; 

byte matrix[] = {0xFF,0xFF,0xFF,0xFF,0,0,0,0};
ArduinoNunchuk nunchuk = ArduinoNunchuk();

int ballX;
int ballY;
void setup()
{
  resetBall();
  nunchuk.init();
  Serial.begin (115200);
  Serial.println ( "Breakout ready  enter 's' or 'd' " );
  for (int i=0; i<18; i++)
    pinMode (i,OUTPUT);
  clearAll();
  timeout = millis() + 500;
  showPaddle (2,p);
}


void showMessage ( char ch)
{
  byte message[] = {0xFF,0xFF,0xFF,0xFF,0,0,0,0};
  switch (ch)
  {
    case 'X':
      message [0] = 0x81;
      message [1] = 0x42;
      message [2] = 0x24;
      message [3] = 0x18;
      message [4] = 0x18;
      message [5] = 0x24;
      message [6] = 0x42;
      message [7] = 0x81;
    break;
    case '(':
      message [0] = 0x18;
      message [1] = 0x42;
      message [2] = 0xA5;
      message [3] = 0x81;
      message [4] = 0x99;
      message [5] = 0x66;
      message [6] = 0x42;
      message [7] = 0x18;
    break;
    case '1':
    message[0] = 0x08;
    message[1] = 0x18;
    message[2] = 0x28;
    message[3] = 0x08;
    message[4] = 0x08;
    message[5] = 0x08;
    message[6] = 0x08;
    message[7] = 0x7e;
    break;
    
    case '2':
    message[0] = 0x18;
    message[1] = 0x24;
    message[2] = 0x24;
    message[3] = 0x08;
    message[4] = 0x10;
    message[5] = 0x20;
    message[6] = 0x20;
    message[7] = 0x3e;
    break;
    
    case '3':
    message[0] = 0x18;
    message[1] = 0x24;
    message[2] = 0x04;
    message[3] = 0x08;
    message[4] = 0x04;
    message[5] = 0x24;
    message[6] = 0x18;
    message[7] = 0x00;
    break;
    
    case '4':
    message[0] = 0x08;
    message[1] = 0x18;
    message[2] = 0x28;
    message[3] = 0x48;
    message[4] = 0xfc;
    message[5] = 0x08;
    message[6] = 0x08;
    message[7] = 0x08;
    break;
    
    case '5':
    message[0] = 0x3e;
    message[1] = 0x20;
    message[2] = 0x20;
    message[3] = 0x3c;
    message[4] = 0x02;
    message[5] = 0x02;
    message[6] = 0x22;
    message[7] = 0x3c;
    break;
  }
    for (int i=0; i<8; i++)
  {
    // Write column i
    digitalWrite (columns[i], 0);
    for (int j=0; j<8; j++)
    {
      if ((bits[j] & message[i]) > 0) 
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

void resetBall()
{
   ballX = 4;
   ballY = 0;  
   yOffset = 0;
   xOffset = 1;
}

// return true if a dot is set at the specified row and column
bool dotIsSet (int column, int row)
{
  bool isSet = false;
  if (matrix[column] & bits[row])
    isSet = true;
  return isSet;
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
/*
  width is width of paddle 
  position is row (y) position
  position can be < 0 this means that less than full paddle will show
*/
void showPaddle (int width, int position) 
{
  bool offOn = false;
  for (int i=0; i<8; i++)
  {
    if ((i <= position + width) && (i >= position))
      setDot (7,i,true);
    else
      setDot (7,i,false);
  }  
}

/*
  When ballY == 7 this is the right wall,
  When ballY == 0, this is the left wall
  When ballX == 7, ball has either hit the paddle or missed
*/
void updateBall () 
{
  static unsigned long ballTime = 0;
  if (ballX != 7)
    setDot (ballX, ballY, false);
  if (millis() > ballTime)
  {
    ballX += xOffset;
    ballY += yOffset;
    if (ballY > 7)
      ballY = 7;
    else if (ballY < 0)
      ballY = 0;
    
    if ((ballX == 7) || (ballX == 0))
      xOffset = 0 - xOffset;
    else if (dotIsSet ( ballX, ballY) ) 
    {
      xOffset = 1;
      yOffset = 0 - yOffset; // reverse direction
    }  
      
    // Switch y directions assuming that y is non-zero  
    if ((ballY == 0) || (ballY == 7))
      yOffset = 0 - yOffset;  
    
    ballTime = millis() + 500;
  }
  
}
void collision (bool & left, bool & right, bool & center, bool & miss)
{
  center = false;
  left = false;
  right = false;
  miss = false;
  
  if (ballX == 7)
  {
    miss = true;
    if (ballY >= p)
      if ((ballY-p) <= 2)
      { 
        miss = false;
        if (ballY == p) 
          left = true;
        else if (ballY == (p + 2)) 
          right = true;
        else
          center = true;       
      }  
  }  
  ballMissed = miss;  
}

void getNunchuk (bool & left, bool & right, bool & startOver)
{
  static unsigned long nunchukTimeout = 0;
  left = false;
  right = false;
  startOver = false;
  if (millis() > nunchukTimeout)
  {
    nunchuk.update(); 
    nunchukTimeout = millis() + 100;
    if (nunchuk.analogX < 60)
      left = true;
    else if (nunchuk.analogX > 180)
      right = true;
    if (nunchuk.zButton)
      startOver = true;  
  }   
}

void loop()
{
  bool left, right, center, miss;
  static bool lastLeft = false;
  static bool lastRight = false;
  static bool lastCenter = false;
  static bool lastMiss = false;
  static unsigned long timeout = 0;
  static bool gameOver = false;
  bool goLeft;
  bool goRight;
  bool startOver;
  char ch;
  
  getNunchuk (goLeft, goRight, startOver);
  if (startOver)
  {
    gameOver = false;
    ballMissed = false;
    ballCount = 0;
    p = 2;
    resetBall();
    matrix [0] = 0xFF;
    matrix [1] = 0xFF;
    matrix [2] = 0xFF;
    matrix [3] = 0xFF;
    matrix [4] = 0;
    matrix [5] = 0;
    matrix [6] = 0;
    matrix [7] = 0;
  }
  if (gameOver)
  {
    showMessage ( 'X' );
  }
  else
  {
    if (goLeft)
    {
      if (p < 7)
      {
        p++;
        showPaddle (2,p);
      }  
    }
    else if (goRight)
    {  
      if (p > -2)
      {
        p--;
        showPaddle (2,p);
      }  
    }      
    
    if (timeout)
    {
      if (millis() > timeout) 
        timeout = 0;
      showMessage ( ballCount + '0');  
    }
    else if (ballMissed)
    {
      ballCount++;
      timeout = millis() + 2300;
      if (ballCount == 6)
        gameOver = true;
      else
        ballMissed = false;
    }
    else
    {  
      updateBall();
      if (Serial.available())
      {
        ch = Serial.read();
        switch (ch)
        { 
          case 10:
          case 13:
          break; // Do nothing
      
          case 's': // paddle left
          if (p < 7)
          {
            p++;
            showPaddle (2,p);
          }  
          break;
      
          case 'd': // paddle right
          if (p > -2)
          {
            p--;
            showPaddle (2,p);
          }  
          break;
      
          default:
            Serial.println ( (int) ch );
          break;  
        }
      }
      collision(left, right, center, miss);
      if ((lastLeft != left) || (lastRight != right) || (lastCenter != center) || (lastMiss != miss))
        if (left)
        {
          Serial.println ( "Go left" );
          yOffset = -1;
        } 
        else if (right) 
        {
          Serial.println ( "Go right" );
          yOffset = 1;
        }
        else if (center)
        {
          Serial.println ( "Go center" );
          yOffset = 0;
        }
        else if (miss)
        {
          Serial.println ( "Miss" );  
          resetBall();
        }
      lastLeft = left;
      lastRight = right;
      lastCenter = center;  
      lastMiss = miss;
      if ((ballX != 7) || ballMissed)
        setDot ( ballX, ballY, true );
      showMatrix ();
    }  
  }     
}
