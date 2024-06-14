#ifndef AVR_GUARD_HPP
#define AVR_GUARD_HPP

#include <stdint.h>

struct avr_guard{
    uint8_t sreg;
    inline void lock(){
        sreg = SREG & (1 << SREG_I);
        cli();
    }
    inline void unlock(){
        SREG |= sreg;
    }

};

#endif//AVR_GUARD_HPP