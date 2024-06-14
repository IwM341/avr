/*
 * P017BASE_CPP.cpp
 *
 * Created: 06.04.2023 21:56:11
 * Author : MainUser
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "../../ave_sig_slot/variant.hpp"
#include "../../framework/process.hpp"

void * operator new(size_t size){
	return malloc(size);
}
void * operator new(size_t size,void *ptr){
	return ptr;
}

void operator delete(void * ptr){
	free(ptr);
}



struct singleton{
	
	static singleton* getInstance(){
		static singleton Instance(123);
		return &Instance;
	}
	private:
	uint8_t x;
	singleton(uint8_t x):x(x){
	}
};

void f(int y){
	static int x = y;
}

inline int g(const int & x){
	return x+1;
}


struct uint24_t{
	uint32_t val:24;	
};
int main(void)
{
    uint24_t x{PORTB+123};
	uint24_t y{PORTB+321};
	uint24_t res {x.val+y.val};
	PORTB = res.val;
	PORTB = res.val>>8; 
}

