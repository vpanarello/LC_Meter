
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
  TCCR1A = 0; //  | COM1  | COM1  | COM1 | COM1  |       |       | WGM11 | WGM10 |
  TCCR1B = 0; //  | ICNC1 | ICES1 |      | WGM13 | WGM12 | CS12  | CS11  | CS10  |
  TCCR1C = 0; //  | FOC1A | FOC1B |      |       |       |       |       |       |

  TCCR1A |= ((output_a << 6) & 0b11000000) | ((output_a << 4) & 0b00110000);
  TCCR1A |= waveform & 0b00000011;
  TCCR1B |= (waveform << 1) & 0b00011000;
  TCCR1B |= clk & 0b00000111;

  /*  Timer/Counter 1 Interrupt Mask Register */
  TIMSK1 = 0;     //  |       |       | ICIE |       |       | OCIEB | OCIEA | TOIE  |
  ICR1 = 0;       /* Input Capture Register 1 (16bits) */
  OCR1A = 0xFFFF; /* Output Compare Register 1 A (16bits) */
  OCR1B = 0xFFFF; /* Output Compare Register 1 B (16bits) */

  TCNT1 = 0; /* Timer Counter 1 (16bits) */
}

void TimerOne::set_cb_comparator_a(void (*cb)())
{
  t1_comparator_a = cb;
  TIMSK1 |= (1 << OCIEA);
}

void TimerOne::set_cb_comparator_b(void (*cb)())
{
  t1_comparator_b = cb;
  TIMSK1 |= (1 << OCIEB);
}

void TimerOne::set_cb_overflow(void (*cb)())
{
  t1_overflow = cb;
  TIMSK1 |= (1 << TOIE);
}

void TimerOne::set_cb_input_capture(void (*cb)())
{
  t1_input_capture = cb;
  TIMSK1 |= (1 << ICIE);
}
