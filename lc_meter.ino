
#include "freq_meter.h"

FrequecyMeter* fm;

void setup()
{
  DDRB |= (1 << 5);
  Serial.begin(9600);
  fm = new FrequecyMeter();

}

void loop()
{
  Serial.print(fm->frequency);
  Serial.println(" Hz");
  delay(1000);
  // PORTB ^= (1 << 5);
}
