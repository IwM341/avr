/*
 * P009MOCUSART.cpp
 *
 * Created: 18.07.2022 16:59:55
 * Author : MainUser
 */ 



#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define UART_QSIZE 32
#include "../../framework/uart_process.hpp"
#include "../../framework/seg7.h"
#include "../../framework/ports.h"

void set7seg(uint8_t m_digit){
	uint16_t seg7 = m_digit << 2;
	set_port(PORTD,0b11111100,seg7);
	set_port(PORTB,0b00000001,seg7>>8);
}

bool blink = false;

void uart::data_recieve_interrupt(uint8_t data){
	if(!uart::uart_process_r().write(data)){
		blink = true;
	}
	else{
		set7seg( digit[(data-'0')%10]);
	}
}

int main(void)
{
    DDRB = 0xFF;
    set_port(DDRD,0b11111100,0xFF);
    sei();
	uart::uart_process_r().open(16,false);
	
	
    while (1) 
    {
		if(blink){
			set_port(PORTB,1<<PORTB5,0xFF);
			_delay_ms(1000);
			set_port(PORTB,1<<PORTB5,0x00);
			blink = false;
		}
    }
}

