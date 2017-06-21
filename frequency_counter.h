#ifndef F_COUNTER_H_
#define F_COUNTER_H_

#include "registers.h"

/* External clock source on T0 pin. Clock on falling edge */
#define EXTERNAL_CLOCK_SOURCE 0x06;
#define NO_CLOCK_SOURCE 0x00;
#define T0_NORMAL_MODE 0x00;
#define DISABLE_OVF_INTERRUPT interrupt->timer_0 &= 0b11111110
#define DISABLE_OVF_INTERRUPT interrupt->timer_0 &= 0b11111110
#define ENABLE_OVF_INTERRUPT interrupt->timer_0 |= 0b00000001

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

    uint32_t* get_counter_pointer();
    void clear_counter();
};

#endif /* F_COUNTER_H_ */