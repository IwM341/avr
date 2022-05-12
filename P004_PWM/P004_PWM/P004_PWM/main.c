/*
 * P004_PWM.c
 *
 * Created: 10.05.2022 19:44:15
 * Author : Artem
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "../../../utils/ports.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>



void init_PWM_timer(void)
{
	ASSR=0x00;
	TCCR0A = (1<<WGM00)| (1<<WGM01)| (1<<COM0A1);
	TCCR0B = 1<<CS00;
	OCR0A = 10; 
	TCNT0 = 0x00;
}

ISR (TIMER0_OVF_vect)
{
	OCR0A ++;
	set_port(PORTD,1<<PORTD7,0xFF); 
	
};
int main(void)
{
	PORTB = 0;
	DDRD = 0xFF;
	init_PWM_timer();
	
	TIMSK0 =	1<<TOIE0;
	sei();
}

