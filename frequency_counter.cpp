
#include "frequency_counter.h"

FrequencyCounter::freq_counter FrequencyCounter::counter = {0};

#define DISABLE_OVF_INTERRUPT interrupt->timer_0 &= 0b11111110
#define ENABLE_OVF_INTERRUPT interrupt->timer_0 |= 0b00000001

ISR(TIMER0_OVF_vect)
{
    FrequencyCounter::counter.parts.high++;
}

uint32_t FrequencyCounter::get_counter() {
    DISABLE_OVF_INTERRUPT;
    counter.parts.low = timer0->counter;
    ENABLE_OVF_INTERRUPT;
    return counter.value;
}

void FrequencyCounter::clear_counter() {
    DISABLE_OVF_INTERRUPT;
    counter.value = 0;
    timer0->counter = 0;
    ENABLE_OVF_INTERRUPT;
    return;
}

FrequencyCounter::FrequencyCounter()
{
    timer0->control_a = 0x00;
    timer0->control_b = 0x05;
    timer0->compare_a = 0xFF;
    ENABLE_OVF_INTERRUPT;
}