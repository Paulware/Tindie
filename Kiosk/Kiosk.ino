// we need this library for the LCD commands
#include <LiquidCrystal.h> 
#include <SPI.h>
#include <Wire.h>
#include <ArduinoNunchuk.h>


#define TWENTYXFOUR
#ifdef TWENTYXFOUR
#define COLUMNS 20
#else
#define COLUMNS 16
#endif
#define ROWS 4

#define NUMPAGES 4
ArduinoNunchuk nunchuk = ArduinoNunchuk();
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int state = 0;
int currentPage = 0;
int x = COLUMNS - 1;
int y = 0;
char info[][4][21] = {
  {
    "   Indiana          ",
    "Indiana's capital is",
    "  Indianapolis      ",
    "                    "
  },
  {
    " the nickname is    ",
    "  hoosier state     ",
    " and state flower   ",
    " is peony           "
  }
,
  {
    " the state tree is  ",
    "tulip tree and the  ",
    " bird is cardinal   ",
    " and the song is    "
  }
,
  {
    " On the Banks of the",
    " Wabash Far Away.   ",
    "                    ",
    "                    "
  }
,
  {
    "                    ",
    "                    ",
    "                    ",
    "                    "
  }
,
  {
    "                    ",
    "                    ",
    "                    ",
    "                    "
  }
,
  {
    "                    ",
    "                    ",
    "                    ",
    "                    "
  }
,
  {
    "                    ",
    "                    ",
    "                    ",
    "                    "
  }
,
  {
    "                    ",
    "                    ",
    "                    ",
    "                    "
  }
,
  {
    "                    ",
    "                    ",
    "                    ",
    "                    "
  }
    
};

void showPage ( int whichPage )
{
  lcd.clear();
  delay(10);
  for (int i=0; i<4; i++)
  {
    lcd.setCursor (0,i);
    lcd.print ( info [whichPage][i]);
  }
}
    
void setup()
{
  Serial.begin (115200);
  nunchuk.init();

  delay(10);
  lcd.begin(COLUMNS, ROWS); // Specify how many columns and rows in the LCD unit
  delay(10);
  showPage (0);
} 

void handleCh()
{
  char ch = 0;
  if (Serial.available())
    ch = Serial.read();

  // Ignore carriage return/line feed
  if ((ch == 10) || (ch == 13)) 
    ch = 0;

  if (ch)
  {
    x = x + 1;
    if (x == COLUMNS) 
    {
      x = 0;
      y = y + 1;
      if (y == ROWS) 
        y = 0;
    } 

    if (ch == '^') // clearscreen
    {
      lcd.clear();
      x = COLUMNS -1;
      y = ROWS - 1;
    }
    else
    {
      lcd.setCursor (x,y);
      lcd.print ( ch );   
    }  
  }    
}

unsigned long timeout = 0;
void readNunChuk ()
{
  static int lastPage = 0;
  
  nunchuk.update();

  if (millis() > timeout)
    if ((nunchuk.analogX < 100) || (nunchuk.analogY < 100))
      currentPage--;
    else if ((nunchuk.analogX > 160) || (nunchuk.analogY > 160))
      currentPage++;
    else if (nunchuk.zButton)
      currentPage++;
    else if (nunchuk.cButton)
      currentPage--;   
  
  if (currentPage != lastPage)
  {
    timeout = millis() + 1000;
    if (currentPage < 0)
      currentPage = NUMPAGES - 1;
    currentPage %= NUMPAGES;
    showPage (currentPage);
    Serial.print ( "CurrentPage: " );
    Serial.println ( currentPage );
  }
  lastPage = currentPage;  
}

void loop()
{
  handleCh ();
  readNunChuk (); 
}

