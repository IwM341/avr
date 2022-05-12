/*
 * P003_Timer.c
 *
 * Created: 08.05.2022 15:56:31
 * Author : Artem
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../../utils/ports.h"

unsigned char i;

void segchar (unsigned char seg)
{
	unsigned char d = seg%10;
	set_port(PORTD,0b00001111,d);
}

void timer_ini(void)
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b00111100; //записываем в регистр число для сравнения
	OCR1AL = 0b10010010;
	TCCR1B |= (1<<CS12);//установим делитель.
}


ISR (TIMER1_COMPA_vect)
{
	if(i>9) {
		i=0;
	}
	segchar(i);
	i++;
}


int main(void)
{
    timer_ini();
    DDRD = 0xFF;
    DDRB = 0x00 | 1<<PORTB5;
	set_port(DDRB,1<<PORTB5,0xFF);
    //PORTB = 0b00000001;
	segchar(5);
    i=0b10101010;
	segchar(6);
	segchar(3);
	segchar(0);
    sei();
}

