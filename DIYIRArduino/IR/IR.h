#ifndef IR_Class_h
#define IR_Class_h

#include <arduino.h>
#include <avr/interrupt.h>

#define MAXIRCOUNTS 16

class IR {

public:
  IR ( int irrcvpin ); // constructor
  
  // methods
  void callback();
  unsigned int decodeBits (int maxLow, bool onOff, bool debug);
  void resetIR();
  
  // fields
  bool irReady;  
  
protected:  
  
private:
  int rcvpin;  
  byte lastIR;
  int onCounts [MAXIRCOUNTS];
  int offCounts[MAXIRCOUNTS];
  int offHead; // head offset always points to next available
  int offTail; // tail offset
  int irCount;
  bool first;
};
#endif