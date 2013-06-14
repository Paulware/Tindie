#include "GraphicUtilities.h"
//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940


#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
// optional


GraphicUtilities::GraphicUtilities (void)
{
  tft = new TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
  // For better pressure precision, we need to know the resistance
  // between X+ and X- Use any multimeter to read it
  // For the one we're using, its 300 ohms across the X plate
  ts = new TouchScreen1(XP, YP, XM, YM, 300);
  fontSize = 1;
}

int GraphicUtilities::width()
{
  return tft->width();
}

int GraphicUtilities::height()
{
  return tft->height();
}

bool GraphicUtilities::mouseDot ( int & x, int & y, unsigned long ms)
{
  bool ok = false;
  static unsigned long timeout = 0;
  Point1 p1;
  Point1 p = ts->getPoint();
  
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    x = p.x;
	y = p.y;
    x = map(x, TS_MINX, TS_MAXX, width(), 0);
    y = map(y, TS_MINY, TS_MAXY, height(), 0);
    x = 240-x;
    y = 320-y;
  
    if (ms > timeout)
    {     
	
      for (int i=0; i<2; i++) // 2 is necessary for proper drawing
      {
	  
	    // Necessary to allow proper drawing
		// Not sure why, but it should not be removed
	    p1 = ts->getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);		
		
        fillCircle(x, y, PENRADIUS+3, RED);        
      }  
      ok = true;
	  timeout = ms + 500;
	}
  }	
  return ok;
}

void GraphicUtilities::setColor (uint16_t color )
{
  currentColor = color;
}

void GraphicUtilities::drawRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color)
{
  tft->drawRect (x0, y0, w, h, color );
}
void GraphicUtilities::fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color)
{
  tft->fillRect (x0, y0, w, h, color );
}
void GraphicUtilities::drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, 
                                     uint16_t h, uint16_t radius, uint16_t color)
{
  tft->drawRoundRect (x0,y0,w,h,radius,color );
}
void GraphicUtilities::fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, 
                                     uint16_t radius, uint16_t color)
{
  tft->fillRoundRect (x0,y0,w,h,radius,color);
}
void GraphicUtilities::drawCircle(uint16_t x0, uint16_t y0, uint16_t r,	uint16_t color)
{
  tft->drawCircle (x0,y0,r,color );
}
void GraphicUtilities::fillCircle(uint16_t x0, uint16_t y0, uint16_t r,	uint16_t color)
{
  tft->fillCircle (x0,y0,r,color );
}

void GraphicUtilities::drawString ( char * line, uint16_t x, uint16_t y, uint16_t color)
{
  // int len = strlen (line);
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->setTextSize(3);
  tft->println ( line );
  //for (int i=0; i<len; i++)
  //   tft->drawChar(x,y,len[i],color,1);
}   

void GraphicUtilities::drawLine ( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color )
{
  tft->drawLine ( x1,y1,x2,y2,color);
}

int GraphicUtilities::getRotation()
{
  return tft->getRotation();
}

void GraphicUtilities::clearScreen()
{
  fillScreen (BLACK);
}

void GraphicUtilities::fillScreen (uint16_t color)
{
  tft->fillScreen(color);
}

void GraphicUtilities::demoRects(void)
{
  tft->fillRect(0, 320-BOXSIZE, BOXSIZE, 320,MAGENTA );
  tft->fillRect(BOXSIZE, 320-BOXSIZE, BOXSIZE, 320,BLUE );
  tft->fillRect(BOXSIZE*2, 320-BOXSIZE, BOXSIZE, 320,CYAN );
  tft->fillRect(BOXSIZE*3, 320-BOXSIZE, BOXSIZE, 320, GREEN);
  tft->fillRect(BOXSIZE*4, 320-BOXSIZE, BOXSIZE, 320, YELLOW);
  tft->fillRect(BOXSIZE*5, 320-BOXSIZE, BOXSIZE, 320, RED);
}

void GraphicUtilities::init(void)
{
  tft->reset();
  uint16_t identifier = tft->readRegister(0x0);
  tft->initDisplay(); 
}