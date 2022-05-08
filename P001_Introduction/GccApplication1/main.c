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
	DDRD = 0xFF;
	
	DDRB = 0x00;
	PORTB = 0x00;
	
    while (1) 
    {
		PORTD = PINB;
    }
}

