/*
 * GccApplication2.c
 *
 * Created: 05.05.2022 13:00:39
 * Author : Artem
 */ 

#include <avr/io.h>
#define  F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

//				   .gfedcba
#define DIGIT7_0 0b00111111
#define DIGIT7_1 0b00000110
#define DIGIT7_2 0b01011011
#define DIGIT7_3 0b01001111
#define DIGIT7_4 0b01100110
#define DIGIT7_5 0b01101101
#define DIGIT7_6 0b01111101
#define DIGIT7_7 0b00000111
#define DIGIT7_8 0b01111111
#define DIGIT7_9 0b01101111
#define DIGIT7_NONE 0b00000000
#define DIGIT7_MINUS 0b01000000


const unsigned char digit[11] = {DIGIT7_0,DIGIT7_1,DIGIT7_2,DIGIT7_3,DIGIT7_4,DIGIT7_5,DIGIT7_6,DIGIT7_7,DIGIT7_8,DIGIT7_9,DIGIT7_NONE};



void to3Digit(unsigned char x, unsigned char _dig[3]){
	_dig[0] = x%10;
	x = x/10;
	_dig[1] = x%10;
	x = x/10;
	_dig[2] = x%10;
	
	if(_dig[2] == 0){
		_dig[2] = 10;
		if(_dig[1] == 0){
			_dig[1] = 10;
		}
	}
}
/*
int main(void)
{
	DDRD = 0xFF;
    while (1) 
    {
		for(unsigned char i=0;i<10;++i){
			PORTD = digit[i];
			_delay_ms(500);
		}
		
    }
}
*/

int main(void)
{
	DDRD = 0b11111100;
	DDRB = 0b00000001;
	
	unsigned char i = 0;
	
	uint16_t tmp;
	while (1)
	{
		tmp = digit[i] << 2;
		PORTD = tmp;
		PORTB = tmp>>8;
		_delay_ms(1000);
		if(i == 9)
			i = 0;
		else
			i++;
	}
}
