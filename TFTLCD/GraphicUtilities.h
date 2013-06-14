/*
   This is a wrapper class which can be implemented once for each 
   type of graphics display so that the next layer program that creates
   custom displays does not need to change when the display changes
*/
#include "TFTLCD.h"
#include "Touchscreen1.h"

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF

// must be an analog pin, use "An" notation!
#define YP A1 
// must be an analog pin, use "An" notation!
#define XM A2  
// can be a digital pin
#define YM  7  
// can be a digital pin
#define XP  6 

// Was A4
#define LCD_RESET A4

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define BOXSIZE 40
#define PENRADIUS 3
 
class GraphicUtilities {
 public:
   GraphicUtilities(void);
   void init(void);
   void demoRects(void);
   void fillScreen (uint16_t color = 0xFFFF);
   bool mouseDot (int & x, int & y, unsigned long ms);   
   
   void fillRect ();
   void setColor (uint16_t color);
   void drawRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
   void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
   void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
   void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
   void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
   void fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
   int width();
   int height();
   void drawString ( char * line, uint16_t x, uint16_t y, uint16_t color);
   void drawLine ( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color );
   void clearScreen();
   int getRotation();
   
   /* inline functions */
   void smallFont() {fontSize = 1; tft->setTextSize(fontSize);};
   void mediumFont(){fontSize = 2; tft->setTextSize(fontSize);};
   void largeFont() {fontSize = 3; tft->setTextSize(fontSize);};
     
 private:
   TFTLCD * tft;
   TouchScreen1 * ts;
   uint16_t currentColor;
   int fontSize;
};
