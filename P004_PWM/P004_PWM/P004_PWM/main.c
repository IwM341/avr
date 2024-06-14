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

unsigned char Up;

void init_PWM_timer(void)
{
	//ASSR=0x00;	//
	TCCR0A = (0<<WGM00)| (1<<WGM01)| (1<<COM0A0) | (0<<COM0B0) | (1<<COM0B1); // Режим fast PWM и сравнение с регистром OCR0A
	TCCR0B = (1<<CS00) | (1<<FOC0B); // Делитель частоты
	OCR0A = 80;  // То, с чем сравниваем
	OCR0B = 50;
	TCNT0 = 0x00; // обнуление счетчика
	TIMSK0  |=	1<<OCIE0A; // Включаем прерывание по переполнению счетчика
}

ISR (TIMER0_COMPA_vect)
{
	/*
	if(Up){
		OCR0A ++;
		if(OCR0A == 0xFF){
			Up = 0;
		}
		
	}
	else{
		OCR0A --;
		if(OCR0A == 0){
			Up = 1;
		}
	}
	*/
	
	set_port(PORTD,1<<PORTD5,0xFF); 
};
int main(void)
{
	DDRB = 1<<PORTB5;
	PORTB = 1<<PORTB5;
	DDRD = 0xFF;
	init_PWM_timer();
	Up = 1;
	sei();
	while(1);
}

