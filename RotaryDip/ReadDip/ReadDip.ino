#define BAUDRATE 115200
#define LOWPIN 2
#define HIPIN 13
unsigned long timeout = 0;


void setup()
{
  Serial.begin(BAUDRATE);
  Serial.println ( "Rotary Dip ready Slave Address = 6" );
  for (int i=HIPIN; i>(LOWPIN-1); i--)
  {
    pinMode (i, INPUT);
    digitalWrite(i,1); // set pull-up resistor
    Serial.print ( " pin " );
    Serial.print ( i );
    Serial.println ( " pull-up" );
  }
}

int readPins()
{
  int values[] = {0,0,2,4,8,1,40,20,10,80, 400, 200, 100, 800};
  int value = 0;     
    
  for (int i=HIPIN; i>(LOWPIN-1); i--)
    if (!digitalRead (i))
      value += values[i];
  return value;
}

void loop()
{
  static int lastPins = 0;
  int pins = readPins();
  if (pins != lastPins)
  {
    Serial.print ( "pins: " );
    Serial.println ( pins);
  }
  lastPins = pins;
}
