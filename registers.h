
#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Arduino.h"

#define PORTS_ADDRESS 0x23
struct ports_registers {
    byte read_b;
    byte direction_b;
    byte state_b;
    byte read_c;
    byte direction_c;
    byte state_c;
    byte read_d;
    byte direction_d;
    byte state_d;
};

#define INTERRUPTS_ADDRESS 0x6B
struct interrupts_registers
{
    byte pin_change_0;
    byte pin_change_1;
    byte pin_change_2;
    byte timer_0; //TIMSK0
    byte timer_1;
    byte timer_2;
};

#define TIMER0_ADDRESS 0x43
struct timer_0_registers
{
    byte general_control; // GTCCR
    byte control_a;       // TCCR0A
    byte control_b;       // TCCR0B
    byte counter;         // TCNT0
    byte compare_a;       // OCR0A
    byte compare_b;       // OCR0B
};

extern ports_registers *ports;
extern interrupts_registers *interrupt;
extern timer_0_registers *timer0;

#endif /* REGISTERS_H_ */