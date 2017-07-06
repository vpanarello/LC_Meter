#ifndef TIMER_ONE_H_
#define TIMER_ONE_H_

#include "Arduino.h"
#include "registers.h"

#define WAVEFORM_NORMAL 0
#define WAVEFORM_PWM_PHASE_CORRECT_8BIT 1
#define WAVEFORM_PWM_PHASE_CORRECT_9BIT 2
#define WAVEFORM_PWM_PHASE_CORRECT_10BIT 3
#define WAVEFORM_CTC_OCR1A 4 /*Clear Timer on Compare Match */
#define WAVEFORM_PWM_FAST_8BIT 5
#define WAVEFORM_PWM_FAST_9BIT 6
#define WAVEFORM_PWM_FAST_10BIT 7
#define WAVEFORM_PWM_PHASE_FREQ_CORRECT_A 8
#define WAVEFORM_PWM_PHASE_FREQ_CORRECT_B 9
#define WAVEFORM_PWM_PHASE_CORRECT_ICR1 10
#define WAVEFORM_PWM_PHASE_CORRECT_OCR1A 11
#define WAVEFORM_CTC_ICR1 12 /*Clear Timer on Compare Match */
#define WAVEFORM_PWM_FAST_ICR1 14
#define WAVEFORM_PWM_FAST_OCR1A 15

#define CLK_DISABLE 0
#define CLK_DIV_1 1
#define CLK_DIV_8 2
#define CLK_DIV_64 3
#define CLK_DIV_256 4
#define CLK_DIV_1024 5
#define CLK_EXTERNAL_FALL 6
#define CLK_EXTERNAL_RISE 7

#define OUTPUT_OFF 0
#define OUTPUT_TOGGLE 1
#define OUTPUT_CLEAR 2
#define OUTPUT_SET 3

/* TIMSK1 bits*/
#define TOIE 0
#define OCIEA 1
#define OCIEB 2
#define ICIE 5


class TimerOne
{
private:
public:

  TimerOne(uint8_t, uint8_t);
  TimerOne(uint8_t, uint8_t, uint8_t, uint8_t);

  void set_cb_comparator_a(void (*cb)());
  void set_cb_comparator_b(void (*cb)());
  void set_cb_overflow(void (*cb)());
  void set_cb_input_capture(void (*cb)());
};

#endif /* TIMER_ONE_H_ */
