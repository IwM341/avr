#define F_CPU 16000000UL
#include <avr/io.h>
#include "../../../utils/ports.h"
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
	if(newlast == _queue->first && _queue->len != 0){
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
queue output;

uint8_t transmit_process_on = 0;
void transmit_act(){
	if(is_empty_queue(&output)){
		transmit_process_on = 0;
	}
	else{
		//set_port(PORTB,1<<PORTB0,0xFF);
		UDR0 = pop_queue(&output);
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
void set7seg(uint8_t);
//receive
ISR(USART_RX_vect){
	//set_port(PORTD,0b00000100,~PORTD);
	push_queue(&input,UDR0);
	//set7seg(input.len);
}


//transmit
ISR (USART_TX_vect){
	//set_port(PORTB,1<<PORTB5,0xFF);
	if(transmit_process_on){
		transmit_act();
	}
}



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


inline void set7seg(uint8_t num){
	uint16_t seg7 = digit[num] << 2;
	set_port(PORTD,0b11111100,seg7);
	set_port(PORTB,0b00000001,seg7>>8);
}


int main(void)
{
	/* Replace with your application code */
	DDRB = 0xFF;
	set_port(DDRD,0b11111100,0xFF);
	sei();
	USART_Init(16);
	
	set_port(PORTD,0b11111100,0x00);	
	
	set_port(PORTD,0b00111100,0xFF);
	_delay_ms(1000);	
	set_port(PORTD,0b00111100,0x00);
	
	while (1)
	{
		//enable_transmit_pocess();
		
		
		if(!is_empty_queue(&input)){
			//set_port(PORTD,0b11111100,0x00);
			//set_port(PORTD,0b00011100,0xFF);
			//_delay_ms(500);
			set_port(PORTD,0b00011100,0x00);
			//_delay_ms(500);
			uint8_t data = pop_queue(&input);
			
			push_queue(&output,data);
			enable_transmit_pocess();
			
			uint8_t num = (data - '0')%10;
			set7seg(num);
		}
	}
}

