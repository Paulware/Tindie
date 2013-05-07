int columns [] = {5,12,13,8,15,7,3,2};
int rows[] = {9,4,17,6,10,16,11,14};
byte bits[] = {1,2,4,8,0x10, 0x20, 0x40, 0x80};
unsigned long timeout = 0;
int x = 0;
int y = 0;

byte matrix[] = {0xFF,0xFF,0xFF,0xFF,0,0,0,0};

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
void setup()
{
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
void spiral ()
{
  static int state = 0;
  static int level = 0;
  if ((x==0) && (y == 0))
    setDot (3,3,false);
  else
    setDot (x,y,false);
  
  switch (state )
  {
    case 0: // Left to right outer 
      x++;
      setDot (x,y,true);
      if ((x+level) == 7) // last one 
        state = 1;
    break;
    case 1: // Top to bottom 
      y++;
      setDot (x,y,true);
      if ((y+level)==7)
        state = 2;
    break;
    case 2: // Right to left 
      x--;
      setDot (x,y,true);
      if ((x-level)==0)
        state = 3;
      
    break;
    case 3: // Bottom to top
      y--;
      setDot (x,y,true);
      if ((y-level-1)<=0)
      {
        state = 0;
        level++;
        if (level == 4) 
        {
          setDot (x,y,false);
          x = 0;
          y = 0;
          level = 0;
        }  
      }
    break; 
  }
  delay (20);
}


/*
  width is width of paddle 
  position is row (y) position
*/
void paddle (int width, int position) 
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

void showBall () 
{
  static int ballX = 4;
  static int ballY = 0;
  static int offsetX = 1;
  static int offsetY = 0;
  static unsigned long ballTime = 0;
  setDot (ballX, ballY, false);
  if (millis() > ballTime)
  {
    ballX += offsetX;
    ballY += offsetY;
    if (ballX == 7)
      offsetX = -1;
    else if (ballX == 3)
      offsetX = 1;  
    
    ballTime = millis() + 500;
  }
  setDot ( ballX, ballY, true );
}
int p = 0;
int width = 2;
int showNow = 0;
void loop()
{
  //spiral();
  if (millis() > timeout)
  {
    paddle (2,p);
    p++;
    p %= 6;
    timeout = millis() + 500;
  }
  showBall();
  showMatrix ();
}
