
#include "keyboard.h"

Keyboard::Keyboard()
{
    set_output_port(ports->direction_b, KEYPIN_A);
    set_output_port(ports->direction_b, KEYPIN_B);
    set_output_port(ports->direction_e, KEYPIN_C);
    set_input_port(ports->direction_f, KEYSTATUS);
    
    added_keys = 0;
    key = 0;

    callbacks = (cb_pointer *)malloc(sizeof(cb_pointer) * NUMBER_OF_KEYS);
}

#define BIT_A 0
#define BIT_B 1
#define BIT_C 2

void Keyboard::set_address(uint8_t addr)
{
    copy_bit_to_pin(ports->state_b, KEYPIN_A, addr, BIT_A);
    copy_bit_to_pin(ports->state_b, KEYPIN_B, addr, BIT_B);
    copy_bit_to_pin(ports->state_e, KEYPIN_C, addr, BIT_C);
    _delay_us(5);
}

void Keyboard::set_callback(cb_pointer cb)
{
    if (added_keys < NUMBER_OF_KEYS)
    {
        callbacks[added_keys++] = cb;
    }
}


void Keyboard::check_keys()
{
    set_address(key);
    boolean pressed = ~read_state(ports->read_f, KEYSTATUS);

    if (pressed && key < added_keys)
    {
        callbacks[key]();
        _delay_ms(TIME_TO_KEY_RELEASE);
        pressed = ~read_state(ports->read_f, KEYSTATUS);
        if(pressed) _delay_ms(TIME_TO_REPEAT_KEY_PRESSED);
    }
    key++;
    if (key >= NUMBER_OF_KEYS)
    {
        key = 0;
    }
}
