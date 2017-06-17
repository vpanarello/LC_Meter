#ifndef F_COUNTER_H_
#define F_COUNTER_H_

#include "registers.h"

class FrequencyCounter
{
  private:
  public:
    FrequencyCounter();
    union freq_counter {
        uint32_t value;
        struct
        {
            uint8_t low;
            uint32_t high;
        } parts;
    };
    static freq_counter counter;

    uint32_t get_counter();
    void clear_counter();
};

#endif /* F_COUNTER_H_ */