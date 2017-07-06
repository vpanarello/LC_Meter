
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
    byte read_e;
    byte direction_e;
    byte state_e;
    byte read_f;
    byte direction_f;
    byte state_f;
};

#define INTERRUPTS_ADDRESS 0x6B
struct interrupts_registers
{
    byte pin_change_0;
    byte reserved_00;
    byte reserved_01;
    byte timer_0; //TIMSK0
    byte timer_1;
    byte reserved_02;
    byte timer_3;
    byte timer_4;
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

#define TIMER1_ADDRESS 0x80
struct timer_1_registers
{
    byte control_a;
    byte control_b;
    byte control_c;
    byte reserved_01;
    uint16_t counter;
    uint16_t capture;
    uint16_t compare_a;
    uint16_t compare_b;
    uint16_t compare_c;
};

extern ports_registers *ports;
extern interrupts_registers *interrupt;
extern timer_0_registers *timer0;
extern timer_1_registers *timer1;

#endif /* REGISTERS_H_ */
