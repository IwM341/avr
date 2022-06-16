/*
 * P006USART.c
 *
 * Created: 21.05.2022 20:02:34
 * Author : Artem
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "../../utils/ports.h"
#include <avr/interrupt.h>

#include <util/delay.h>

#include <stdio.h>

#include <stdlib.h>
	

//usart speed BAUD  = F_CPU/(1+UBBRn)/16
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

#define QSIZE 100
typedef struct tagqueue{
	uint8_t data[QSIZE];
	uint8_t first;
	uint8_t len;
} queue;

inline uint8_t is_empty_queue(queue * _queue){
	return _queue->len == 0;
}

inline uint8_t push_queue(queue * _queue,uint8_t data){
	uint8_t newlast = (_queue->first + _queue->len)%QSIZE;
	if(newlast == _queue->first){
		return 1;
	}
	else{
		_queue->data[newlast] = data;
		_queue->len ++;
		return 0;
	}
}

inline uint8_t pop_queue(queue * _queue){
	uint8_t first = _queue->first;
	_queue->first ++;
	_queue->len --;
	return _queue->data[first];
}

queue input;

uint8_t transmit_process_on = 0;
void transmit_act(){
	if(is_empty_queue(&input)){
		transmit_process_on = 0;
	}
	else{
		set_port(PORTB,1<<PORTB5,0xFF);
		UDR0 = pop_queue(&input);
	}
};
void enable_transmit_pocess(){
	if(!transmit_process_on){
		transmit_process_on = 1;
		if(UCSR0A & (1<<UDRE0)){
			//PORTB = ~PORTB;
			transmit_act();
		}
	}
}

//receive
ISR(USART_RX_vect){
	set_port(PORTB,1<<PORTB0,~PORTB);
	push_queue(&input,UDR0);
	enable_transmit_pocess();
}


//transmit
ISR (USART_TX_vect){
	set_port(PORTB,1<<PORTB5,0xFF);
	if(transmit_process_on){
		transmit_act();
	}
}



int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	set_port(PORTB,1<<PORTB5,0xFF);
	_delay_ms(1000);
	set_port(PORTB,1<<PORTB5,0x00);
	_delay_ms(1000);
	sei();
	push_queue(&input,'h');
	push_queue(&input,'e');
	push_queue(&input,'l');
	push_queue(&input,'l');
	//push_queue(&input,'o');
	USART_Init(16);
	enable_transmit_pocess();
	
    while (1) 
    {
		_delay_ms(5000);
		set_port(PORTB,1<<PORTB0,0x00);
    }
}

