#include <Arduino.h>
#include <Microduino_Key.h>
DigitalKey key_6(6);

    int tempo=0;
    int maxTempo=0;

void setup()
{
    key_6.begin(INPUT_PULLUP);

    Serial.begin(9600);
}

void loop()
{
    if((key_6.readVal(KEY_PRESSED)))
    {
        tone(10, 900);
        tempo++;
    }
    else
    {
      noTone(10);

          if(tempo > 1000 && tempo <= 10000)
          {
            Serial.print('.'); 
          }
          else if(tempo > 10000)
          {
            Serial.print('-');
          }

       tempo = 0;
    }
}
