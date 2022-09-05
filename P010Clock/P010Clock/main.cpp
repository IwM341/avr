/*
 * P010Clock.cpp
 *
 * Created: 19.07.2022 12:49:27
 * Author : MainUser
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../framework/scheduler_process.hpp"
#include "../../framework/seg7.h"
#include "../../framework/ports.h"

void set7seg(uint8_t m_digit){
	uint16_t seg7 = m_digit << 2;
	set_port(PORTD,0b11111100,seg7);
	set_port(PORTB,0b00000001,seg7>>8);
}

struct my_clock{
	uint8_t c1,c2,c3,c4;
	uint8_t mask;
	void set_time(){
		scheduler::_data D  = scheduler::scheduler_r().data_clock();
		c1 = digit[D.minuts / 10];
		c2 = digit[D.minuts % 10];
		c3 = digit[D.seconds / 10];
		c4 = digit[D.seconds % 10];
		scheduler::scheduler_r().conect_by_delta_clock(1000,this,&my_clock::set_time);
	}
	void change_mask(){
		switch (mask)
		{
			case 0b00000010: {
				set7seg(c2);
				mask = 0b00000100;
				break;
			}
			case 0b00000100:{
				set7seg(c3);
				mask = 0b00001000;
				break;
			}
			case 0b00001000:{
				set7seg(c4);
				mask = 0b00010000;
				break;
			}
			case 0b00010000:{
				set7seg(c1);
				mask = 0b00000010;
				break;
			}
			default:{
				mask = 0b00000010;
				break;
			}
		}
		set_port(PORTB,0b00011110,mask);
		scheduler::scheduler_r().conect_by_delta_clock(20,this,&my_clock::change_mask);
	}
	void init(){
		mask = 0b00000100;
		set_time();
		change_mask();
	}
};

int main(void)
{
	DDRB = 0xFF;
	set_port(DDRD,0b11111100,0xFF);
	sei();
	my_clock clk;
	clk.init();
    scheduler::scheduler_r().init();
	
	
    while (1) 
    {
		/*
		uint8_t mOCRA  = OCR0A;
		clk.c1 = digit[mOCRA / 100];
		clk.c2 = digit[(mOCRA % 100) / 10];
		clk.c3 = digit[mOCRA % 10];
		_delay_ms(2000);
		uint8_t mTCCR0B = TCCR0B;
		clk.c1 = digit[(mTCCR0B % 8 ) >> 2];
		clk.c2 = digit[(mTCCR0B % 4 ) >> 1];
		clk.c3 = digit[mTCCR0B % 2];
		_delay_ms(2000);
		*/
		/*
		clk.set_time();
		for(uint8_t i=0;i<4;++i){
			clk.change_mask();
			_delay_ms(20);
		}
		*/
		
    }
}

