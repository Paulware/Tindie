#include "IR.h"
#include "arduino.h"

IR::IR (int irrcvpin )
{
  rcvpin = irrcvpin;
  pinMode (rcvpin, INPUT);
  resetIR();
}

// Reset all on/off information 
void IR::resetIR()
{
  for (int i=0; i<MAXIRCOUNTS; i++)
  {
    onCounts [i] = 0;
    offCounts[i] = 0;
  }
  lastIR = 1; // off inverse logic
  irCount = 0;
  first = true;
  offHead = 0;
  offTail = 0;
  irReady = false;
}

// This procedure will run at 50 microseconds
void IR::callback() 
{
  if (!irReady) // Not ready to be consumed yet
  {
    byte ir = digitalRead (rcvpin); 
    if (ir != lastIR)
    {
      if (ir) // transition to off
      {
        onCounts[offHead] = irCount;
        if (offHead == offTail) // Queue is full, lose one tail value
          offTail = ++offTail % MAXIRCOUNTS;
        // Increment Head/Tail
        offHead = ++offHead % MAXIRCOUNTS;
      }
      else // transition to on 
      {
        /* 
          The first transition to on should be preceded by a 
          long off period.  This period is variable and has 
          nothing to do with the actual pulses being generated.
        */
        if (first) // ignore 
          offCounts[offHead] = 0;
        else
          offCounts[offHead] = irCount;
        first = false;  
      }
      irCount = 0;
    }
    
    if (ir) // pulse is off 
    {
      if (!first) // ir is off (reverse logic)
      {
        if (irCount < 1500)
          irCount = irCount + 1;
        else 
          irReady = true; // It has been off long enough
      }
    }
    else if (irCount < 32767) 
      irCount = irCount + 1;
    
    lastIR = ir;
  }  
}

// Decode where information is defined in the off-time rather than the 
// standard on-time.
unsigned int IR::decodeBits (int maxLow, bool onOff, bool debug)
{
  int counts;
  int head = offHead;
  int tail = offTail;
  unsigned int val; 
  bool first = true;
  val = 0;
  
  if (irReady)
  {  
    if (debug)
	{
     Serial.print ( "head: " );
  	  Serial.print ( head );
  	  Serial.print ( " tail:" );
	  Serial.println ( tail );
	}  

    while ((head != tail) || first) 
    {  
	  first = false;
      if (onOff) 
        counts = onCounts[tail];
      else
        counts = offCounts[tail];
      val = val * 2;
      if (counts > maxLow) 
        val++;
      tail = ++tail % MAXIRCOUNTS;
    } 

    if (debug)
    {  
      head = offHead;
      tail = offTail;
      val = 0;
	  first = true;
      while ((head != tail) || first)
      { 
        first = false;	  
        if (onOff)
          counts = onCounts[tail];
        else  
          counts = offCounts[tail];
        val = val * 2;
        if (counts > maxLow) 
          val++;
        if (debug)
        { 
          Serial.print ( "[" );
		  if (tail <10)
		    Serial.print ( "0" );
          Serial.print ( tail );
          Serial.print ( "]: " );
          Serial.println (counts);
        }
        tail = ++tail % MAXIRCOUNTS;
      } 
	  if (onOff)
	    Serial.print ("Decoded ON bits maxLow(");
	  else
        Serial.print ("Decoded OFF bits maxLow(" );
      Serial.print ( maxLow );
      Serial.print ( "):");
      Serial.println ( val,HEX );
    }    
  }
  return val;
}
