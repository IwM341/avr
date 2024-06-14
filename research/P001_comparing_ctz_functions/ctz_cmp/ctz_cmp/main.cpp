/*
 * ctz_cmp.cpp
 *
 * Created: 30.08.2023 18:10:53
 * Author : MainUser
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/builtins.h>

volatile static uint16_t full_count;
void timer_ini(void)
{
	//TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	full_count = 0;
	TIMSK1 |= (1<<TOIE1);	// Overflow Interrupt Enable
	TCCR1B |= (1<<CS10);//установим делитель.
	TCNT1L = 0;
	TCNT1H = 0;
}

ISR (TIMER1_OVF_vect) //тело прерывания
{
	full_count++;
}

uint32_t m_clock(){
	uint32_t result = 0;
	
	reinterpret_cast<uint8_t*>(&result)[0] = TCNT1L;
	reinterpret_cast<uint8_t*>(&result)[1] = TCNT1H;
	reinterpret_cast<uint16_t*>(&result)[2] = full_count;
	return result;
}


inline uint8_t my_ctz(uint8_t x){
	#define i1  0b00001111
	#define i2  0b00000011
	#define i3  0b00000001
	
	uint8_t cnt = 0;
	if( !(x & i1)){
		//x = x >> 4;
		
		asm(
			"swap %0"
			:"=r" (x) : "0" (x) :
		);
		
		cnt += 4;
	}
	if(!(x & i2)){
		x = x >> 2;
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

/*
inline uint8_t my_ctz_asm(uint8_t x){
	asm(
		"mov r24 %0\n"
		"andi r24 0x0F\n"
		"brne label_go_next\n"
		"label_second_part:\n"
		"swap r24\n"
		"ldi r19 0x04\n"
		"label_go_next:\n"
		"andi r24 0x03\n"
		"brne label_go_next1\n"
		"lsr r24\n"
		"lsr r24\n"
		"addi r19 0x02\n"
		"label_go_next1:\n"
		"andi r24 0x01\n"
		"brne label_finish\n"
		"andi r24 0xFF"
		"brne label_plus_1\n"
		"addi r19 0x02\n"
		"label_plus_1:\n"
		"addi r19 0x01\n"
		"label_finish:\n" : 
		"=r" (r19) : "0" : (x)
	);
	return r19;
}
*/
inline uint8_t my_ctz_asm(uint8_t x) {
	uint8_t result, temp;

	asm(
	"mov %[result], %[input]     ; Copy x to result\n"
	"andi %[result], 0x0F       ; Clear upper nibble\n"
	"brne 1f                     ; Branch if not equal to 0\n"
	"swap %[result]              ; Swap nibbles\n"
	"ldi %[temp], 0x04           ; Load 0x04 to temp\n"
	"1:                          ; Label for the next part\n"
	"andi %[result], 0x03       ; Clear upper 6 bits\n"
	"brne 2f                     ; Branch if not equal to 0\n"
	"lsr %[result]               ; Logical right shift by 1\n"
	"lsr %[result]               ; Logical right shift by 1\n"
	"subi %[temp], -0x02          ; Add 0x02 to temp\n"
	"2:                          ; Label for the next part\n"
	"andi %[result], 0x01       ; Clear upper 7 bits\n"
	"brne 3f                     ; Branch if not equal to 0\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	"andi %[result], 0xFF       ; Clear upper 8 bits\n"
	"brne 3f                     ; Branch if not equal to 0\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	"3:                          ; Label for the next part\n"
	: [result] "=r" (result), [temp] "=r" (temp)
	: [input] "r" (x)
	);

	return result;
}

uint8_t my_ctz2(uint8_t x) {
	uint8_t input,temp = 0;

	asm(
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"andi %[input], 0x01         ; check is lowest bit is 1\n"
	"brne bit_found              ; Branch if not equal to 0\n"
	"lsr %[input]               ; Logical right shift by 1\n"
	"subi %[temp], -0x01          ; Add 0x01 to temp\n"
	""
	"bit_found:                          ; Label for the next part\n"
	: [temp] "=r" (temp)
	: [input] "r" (x)
	);

	return temp;
}

inline uint8_t my_ctz_asm2(uint8_t x) {
	uint8_t result = 0;
	if(!(x & 1)){
		result++;
		x = x>>1;
	} else {
		goto end; 
	}
	if(!(x & 1)){
		result++;
		x = x>>1;
		} else {
		goto end;
	}
	if(!(x & 1)){
		result++;
		x = x>>1;
		} else {
		goto end;
	}
	if(!(x & 1)){
		result++;
		x = x>>1;
		} else {
		goto end;
	}
	if(!(x & 1)){
		result++;
		x = x>>1;
		} else {
		goto end;
	}
	if(!(x & 1)){
		result++;
		x = x>>1;
		} else {
		goto end;
	}
	if(!(x & 1)){
		result++;
		x>>1;
		} else {
		goto end;
	}
	if(!(x & 1)){
		result++;
		x>>1;
		} else {
		goto end;
	}	
	end:
	return result;
}

int main(void)
{
	volatile int __cycl;
	sei();
    timer_ini();
	
	uint8_t test_data = 0;
	
	volatile uint32_t t0 = m_clock();
	volatile uint8_t result;
	
	do{
		result = my_ctz(test_data);
		test_data++;
	} while (test_data);
	
	volatile uint32_t t1 = m_clock();
	
	volatile float av_delta = (t1-t0)/256.0;
	
    while (1) 
    {
		__cycl++;
    }
}

