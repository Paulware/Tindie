// we need this library for the LCD commands
#include <LiquidCrystal.h> 
#include <SPI.h>

#define TWENTYXFOUR
#ifdef TWENTYXFOUR
#define COLUMNS 20
#else
#define COLUMNS 16
#endif
#define ROWS 4

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int state = 0;
int x = COLUMNS - 1;
int y = 0;
void setup()
{
  Serial.begin (115200);
  delay(10);
  lcd.begin(COLUMNS, ROWS); // Specify how many columns and rows in the LCD unit
  delay(10);
  lcd.clear();
  delay(10);
  #ifdef TWENTYXFOUR
  lcd.print(" HD44780 LCD Ready  ");
  lcd.setCursor (0,1); // necessary
  lcd.print("All digits check out");
  lcd.setCursor (0,2); // necessary
  lcd.print("That is all...Have a");
  lcd.setCursor (0,3); // necessary
  lcd.print("Great Day! Adios bye");
  #else
  lcd.print(" HD44780 Ready  ");
  lcd.setCursor (0,1); // necessary
  lcd.print("All digits check");
  lcd.setCursor (0,2); // necessary
  lcd.print("That is all...");
  lcd.setCursor (0,3); // necessary
  lcd.print("Great Day! Adios");
  #endif
  
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

void loop()
{
  handleCh ();
}
