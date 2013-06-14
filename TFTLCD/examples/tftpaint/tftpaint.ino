#include <GraphicUtilities.h>
GraphicUtilities graphics;
int currentcolor;
void setup()
{
  graphics.init();
  graphics.fillScreen(BLACK);
  graphics.demoRects();
  currentcolor = RED; 
  pinMode(13, OUTPUT);
}

void loop () 
{
  digitalWrite(13, HIGH);
  Point1 p = graphics.getPoint();
  digitalWrite(13, LOW);


  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

    
    if (p.y < (TS_MINY-5)) {
      Serial.println("erase");
     // press the bottom of the screen to erase 
      graphics.fillRect(0, BOXSIZE, graphics.width(), graphics.height()-BOXSIZE, BLACK);
      
    }
    // turn from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, graphics.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, graphics.height(), 0);

    if (p.y < BOXSIZE) {
   
       if (p.x < BOXSIZE) { 
         currentcolor = RED; 
      //   tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
       } 
       else if (p.x < BOXSIZE*2) {
         currentcolor = YELLOW; 
       //  tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*3) {
         currentcolor = GREEN; 
       //  tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*4) {
         currentcolor = CYAN; 
      //   tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*5) {
         currentcolor = BLUE; 
         //      tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*6) {
         currentcolor = MAGENTA; 
         //  tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       
    }
    if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < graphics.height())) {
      graphics.fillCircle(240-p.x, 320-p.y, PENRADIUS, currentcolor);
    }
  }
}

