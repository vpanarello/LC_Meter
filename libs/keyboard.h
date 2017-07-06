
#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include "Arduino.h"
#include "registers.h"

#define NUMBER_OF_KEYS 6

#define TIME_TO_KEY_RELEASE 1
#define TIME_TO_REPEAT_KEY_PRESSED 400

#define KEYPIN_A 4  /* PORTB */
#define KEYPIN_B 5  /* PORTB */
#define KEYPIN_C 6  /* PORTE */
#define KEYSTATUS 5 /* PORTF */

/* Library Macros */
#define copy_bit_to_pin(port, pin, origin, origin_bit) port = (port & ~(1 << pin)) | ((origin << (pin - origin_bit)) & (1 << pin))
#define read_state(input_register, pin) (input_register >> pin) & 0x1;

#define set_output_port(direction_register, pin) direction_register |= (1 << pin)
#define set_input_port(direction_register, pin) direction_register &= ~(1 << pin)

class Keyboard {
    private:
        typedef void (*cb_pointer)();
        cb_pointer* callbacks;
        uint8_t key;
        uint8_t added_keys;
        void set_address(uint8_t) ;

    public:
        Keyboard();
        void set_callback(cb_pointer);
        void check_keys();

};

#endif /* KEYBOARD_H_ */