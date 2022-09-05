/*
 * P003_Timer.c
 *
 * Created: 08.05.2022 15:56:31
 * Author : Artem
 */ 
#define F_CPU 16000000UL
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

void timer_ini(uint16_t mOCRA)
{
	TCCR1B = (1<<WGM12) | (1<<CS12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 = (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = (unsigned char)(mOCRA>>8); //записываем в регистр число для сравнения
	OCR1AL = (unsigned char) mOCRA; //записываем в регистр число для сравнения
	//TCCR1B |= (1<<CS12);//установим делитель.
}

void USART_send(uint8_t data);
char c = 's';
ISR (TIMER1_COMPA_vect) //тело прерывания
{
	USART_send(c);
	//USART_send('\n');
	c = 'c';
}

void USART_Init( unsigned int UBBRn)//Инициализация модуля USART
{
	UBRR0H = (unsigned char)(UBBRn>>8);
	UBRR0L = (unsigned char)UBBRn;
	
	// UCSRnA:
	//UCSR0A |= (1<<U2X0); // удвоение скорости
	
	// UCSRnB:
	UCSR0B = (1<<RXEN0)|( 1<<TXEN0); //Включаем прием и передачу по USART
	UCSR0B |= (1<<RXCIE0) | (1<<TXCIE0); //Разрешаем прерывание при  приеме и передаче
	//UCSZn2 = 1 для 9 бит
	
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);// Обращаемся именно к регистру UCSRnC,
	//USBS0 = 1 - 2 стоп-бита
	//UMSELn - синхронный/асинхронный
	//1 стоп-бит (USBS=0), 8-бит посылка (UCSZ1=1 и UCSZ0=1)
	//UCSRC |= (1<<UPMn1);//четность
}



void USART_send(uint8_t data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

ISR(USART_RX_vect){
	USART_send(UDR0);
}
ISR(USART_TX_vect){	
}

int main(void)
{
	sei();
    timer_ini(62500-1);
    USART_Init(8);
	while(1){
		_delay_ms(1000);
	}
}

