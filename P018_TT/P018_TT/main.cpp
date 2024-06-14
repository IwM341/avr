/*
 * P018_TT.cpp
 *
 * Created: 07.04.2023 21:41:15
 * Author : MainUser
 */ 

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stddef.h>
//#include <avr/sleep.h>
//#include <test.h>

#ifdef 	__AVR_ATmega328P__
template <uint8_t size>
struct struct_of_size{
	char data[size];	
};
#endif

bool flag;


void timer_ini(void)
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим —“— (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A);	//устанавливаем бит разрешени€ прерывани€ 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b00111100; //записываем в регистр число дл€ сравнени€
	OCR1AL = 0b10010010; //записываем в регистр число дл€ сравнени€
	TCCR1B |= (1<<CS12);//установим делитель.
}

ISR (TIMER1_COMPA_vect) //тело прерывани€
{
	flag = !flag;
}

struct S{
	size_t i;	
};
struct M{
	uint32_t x;
	char y;
};
struct virtual_struct{
	virtual void f();
	virtual void g();
	virtual ~virtual_struct(){}
};
struct v_inh:public virtual_struct{
	void f(){}	
	void g(){}	
};

constexpr inline uint8_t my_popcount(uint8_t x){
	constexpr uint8_t i1 =  0b10101010;
	constexpr uint8_t i2 =  0b11001100;
	constexpr uint8_t i3 =  0b11110000;
	
	x = (x & ~i1)  + ((x & i1) >> 1);
	x = (x & ~i2)  + ((x & i2) >> 2);
	x = (x & ~i3)  + ((x & i3) >> 4);
	return x;
}

inline uint8_t asm_popcount(uint8_t x){
	 constexpr uint8_t i1 =  0b10101010;
	 constexpr uint8_t i2 =  0b11001100;
	 constexpr uint8_t i3 =  0b11110000;
	 
	 x = (x & ~i1)  + ((x & i1) >> 1);
	 x = (x & ~i2)  + ((x & i2) >> 2);
	 x = (x & ~i3)  + ((x & i3) >> 4);
	 return x;
 }

uint8_t my_ctz(uint8_t x){
	constexpr uint8_t i1 =  0b00001111;
	constexpr uint8_t i2 =  0b00000011;
	constexpr uint8_t i3 =  0b00000001;
	
	uint8_t cnt = 0;
	if( !(x & i1)){
		x >> 4;
		cnt += 4;	
	}
	if(!(x & i2)){
		cnt += 2;
	}
	if(x & i3){
		return cnt;
	}
	else {
		if(x)
			return cnt + 1;
		else 
			return 8;
	}
}

uint8_t LBF(){
	uint16_t helper =0xAABB;
	if( reinterpret_cast<uint8_t *>(&helper)[0] == 0xBB &&  reinterpret_cast<uint8_t *>(&helper)[1] == 0xAA ){
		return 1;
	} else if( reinterpret_cast<uint8_t *>(&helper)[0] == 0xAA &&  reinterpret_cast<uint8_t *>(&helper)[1] == 0xBB  ){
		return 0;
	} else {
		return 2;
	}
}

int main(void){
	volatile uint8_t  x = alignof(max_align_t);
	
	
	
	volatile size_t y = sizeof(void (M::*)(void));;
    
	volatile uint8_t z = ((x+3)/4)*4;  
	volatile uint8_t z1 = (x % 4 == 0 ? x : (x + 4) & ~(4-1) );  
	
	volatile uint8_t z2 = (x+3)&3;
	
	volatile uint8_t is_lbf = LBF();
	
	volatile uint8_t a = sizeof(S);
	volatile uint8_t b = sizeof(M);
	
	virtual_struct * vs = (virtual_struct *)DDRD;
	
	volatile uint8_t ctz_blt = __builtin_ctz(a);
	volatile uint8_t ctz_my = my_ctz(a);
	
	vs->f();
	vs->g();
	
	sei();
	timer_ini();
	DDRD = 0xFF;
	while (1) {
		if(flag){
			PORTD = 0xFF;
		}
		else{
			PORTD = 0x00;
		}
    }
}

