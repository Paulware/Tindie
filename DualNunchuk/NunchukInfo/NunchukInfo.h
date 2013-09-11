#ifndef NunchukInfo_H
#define NunchukInfo_H

#include "ArduinoNunchuk.h"

struct NunStruct
{
  int x;
  int y;
  bool cButton;
  bool zButton;
  int accelX;
  int accelY;
  int accelZ;
};

#define MAXNUNCHUKCHARS 30

class NunchukInfo
{
  public:
    static bool nunchukDelta (ArduinoNunchuk nunchuk, struct NunStruct & last);
    static bool nunchukDelta (struct NunStruct nunchuk, struct NunStruct & last);
    static void writeChuk (int id, struct NunStruct nunchuk,char * str);
    static void readChuk  (int & id, NunStruct & n, char ch);
  private:
    static void writeNum ( int num, char * str ); 
};
#endif
