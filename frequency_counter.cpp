
#include "frequency_counter.h"

FrequencyCounter::freq_counter FrequencyCounter::counter = {0};

ISR(TIMER0_OVF_vect)
{
    FrequencyCounter::counter.parts.high++;
}

uint32_t* FrequencyCounter::get_counter_pointer() {
    counter.parts.low = timer0->counter;
    return &counter.value;
}

void FrequencyCounter::clear_counter() {
    counter.value = 0;
    timer0->counter = 0;
    return;
}

FrequencyCounter::FrequencyCounter()
{
    /* frequency input pin PD7 (pin 6) */
    ports->direction_d &= ~(1 << 7);
    ports->state_d &= ~(1 << 7);

    timer0->control_a = T0_NORMAL_MODE;
    timer0->control_b = EXTERNAL_CLOCK_SOURCE;
    timer0->compare_a = 0xFF;
    ENABLE_OVF_INTERRUPT;
}