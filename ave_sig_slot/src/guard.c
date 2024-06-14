#include <guard.h>
#include <avr/interrupts.h>


void __guard__lock(__guard__ *g){
	g->sregOld = SREG;
	cli();
	g->sregOld &= 0x80;
}

void __guard__lock(__guard__ *g){
	SREG |= g->sregOld;
}