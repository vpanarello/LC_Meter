
#include "freq_meter.h"
#include "timer_one.h"

#define COUNTER_TO_1HZ 62500

uint32_t FrequecyMeter::counter = 0;
uint32_t FrequecyMeter::frequency = 0;

TimerOne *timer;

ISR(INT0_vect)
{
    FrequecyMeter::counter++;
}

void FrequecyMeter::timer_callback()
{
    frequency = counter;
    counter = 0;
}

FrequecyMeter::FrequecyMeter()
{
    timer = new TimerOne(CLK_DIV_256, WAVEFORM_CTC_OCR1A);
    *timer->compare_a = COUNTER_TO_1HZ;
    timer->set_cb_comparator_a(&timer_callback);

    /*The rising edge of INT0*/
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
    sei();
}
