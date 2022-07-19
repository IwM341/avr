/*
 * P009MOCUSART.cpp
 *
 * Created: 18.07.2022 16:59:55
 * Author : MainUser
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
#define UART_QSIZE 32
#include "../../framework/uart_process.hpp"
#include "../../framework/seg7.h"
#include "../../framework/ports.h"

inline void set7seg(uint8_t num){
	uint16_t seg7 = digit[num] << 2;
	set_port(PORTD,0b11111100,seg7);
	set_port(PORTB,0b00000001,seg7>>8);
}

void uart::data_recieve_interrupt(uint8_t data){
	uart::uart_process_r().write(data);
	set7seg( (data-'0')%10);
}

int main(void)
{
    DDRB = 0xFF;
    set_port(DDRD,0b11111100,0xFF);
    sei();
    while (1) 
    {
    }
}

