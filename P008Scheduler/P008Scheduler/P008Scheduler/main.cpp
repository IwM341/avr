/*
 * P008Scheduler.cpp
 *
 * Created: 09.07.2022 9:26:02
 * Author : MainUser
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include "../../../framework/resources.hpp"
#include "../../../framework/scheduler_process.hpp"
#include "../../../framework/ports.h"


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


void set7seg(uint8_t num){
	uint16_t seg7 = digit[num] << 2;
	set_port(PORTD,0b11111100,seg7);
	set_port(PORTB,0b00000001,seg7>>8);
}
uint8_t i = 0;
void show_i(){
	set7seg(i);
	i = (i + 1)%10;
}

int main(void)
{
	DDRB = 0xFF;
	set_port(DDRD,0b11111100,0xFF);
	sei();
	
	
    auto & mSheduler = scheduler::scheduler_r();
	mSheduler.init();
	mSheduler.conect_by_delta_clock(1000,show_i);
	mSheduler.conect_by_delta_clock(2000,show_i);
	mSheduler.conect_by_delta_clock(3000,show_i);
	mSheduler.conect_by_delta_clock(4000,show_i);
	mSheduler.conect_by_delta_clock(5000,show_i);
	mSheduler.conect_by_delta_clock(6000,show_i);
	mSheduler.conect_by_delta_clock(7000,show_i);
	mSheduler.conect_by_delta_clock(8000,show_i);
	mSheduler.conect_by_delta_clock(9000,show_i);
	
    while (1) 
    {
    }
}

