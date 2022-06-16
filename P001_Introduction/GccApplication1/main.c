/*
 * GccApplication1.c
 *
 * Created: 05.05.2022 11:16:39
 * Author : Artem
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0xFF;
	
    while (1) 
    {
		_delay_ms(1000);
		PORTB = 0x00;
		_delay_ms(1000);
		PORTB = 0xFF;
    }
}

