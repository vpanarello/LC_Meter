
#include "timer_one.h"

void (*t1_comparator_a)() = NULL;
void (*t1_comparator_b)() = NULL;
void (*t1_overflow)() = NULL;
void (*t1_input_capture)() = NULL;

ISR(TIMER1_COMPA_vect)
{
  if (t1_comparator_a)
    t1_comparator_a();
}
ISR(TIMER1_COMPB_vect)
{
  if (t1_comparator_b)
    t1_comparator_b();
}
ISR(TIMER1_OVF_vect)
{
  if (t1_overflow)
    t1_overflow();
}
ISR(TIMER1_CAPT_vect)
{
  if (t1_input_capture)
    t1_input_capture();
}

TimerOne::TimerOne(uint8_t clk, uint8_t waveform)
{
  TimerOne(clk, waveform, OUTPUT_OFF, OUTPUT_OFF);
}

TimerOne::TimerOne(uint8_t clk, uint8_t waveform, uint8_t output_a, uint8_t output_b)
{
  timer1->control_a = 0; //  | COM1  | COM1  | COM1 | COM1  |       |       | WGM11 | WGM10 |
  timer1->control_b = 0; //  | ICNC1 | ICES1 |      | WGM13 | WGM12 | CS12  | CS11  | CS10  |
  timer1->control_c = 0; //  | FOC1A | FOC1B |      |       |       |       |       |       |

  timer1->control_a |= ((output_a << 6) & 0b11000000) | ((output_a << 4) & 0b00110000);
  timer1->control_a |= waveform & 0b00000011;
  timer1->control_b |= (waveform << 1) & 0b00011000;
  timer1->control_b |= clk & 0b00000111;

  /*  Timer/Counter 1 Interrupt Mask Register */
  interrupt->timer_1 = 0;     //  |       |       | ICIE |       | OCIE1C | OCIEB | OCIEA | TOIE  |
  timer1->capture = 0;       /* Input Capture Register 1 (16bits) */
  timer1->compare_a = 0xFFFF; /* Output Compare Register 1 A (16bits) */
  timer1->compare_b = 0xFFFF; /* Output Compare Register 1 B (16bits) */

  timer1->counter = 0; /* Timer Counter 1 (16bits) */
}

void TimerOne::set_cb_comparator_a(void (*cb)())
{
  t1_comparator_a = cb;
  interrupt->timer_1 |= (1 << OCIEA);
}

void TimerOne::set_cb_comparator_b(void (*cb)())
{
  t1_comparator_b = cb;
  interrupt->timer_1 |= (1 << OCIEB);
}

void TimerOne::set_cb_overflow(void (*cb)())
{
  t1_overflow = cb;
  interrupt->timer_1 |= (1 << TOIE);
}

void TimerOne::set_cb_input_capture(void (*cb)())
{
  t1_input_capture = cb;
  interrupt->timer_1 |= (1 << ICIE);
}
