#ifndef FREQ_METER_H_
#define FREQ_METER_H_

#include "Arduino.h"

class FrequecyMeter
{
  private:
    static void timer_callback();
    
  public:
    FrequecyMeter();
    static uint32_t counter;
    static uint32_t frequency;

};

#endif /* FREQ_METER_H_ */
