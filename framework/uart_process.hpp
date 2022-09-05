#ifndef UART_PROCESS_HPP
#define UART_PROCESS_HPP

#include "io_process.hpp"
#include <avr/interrupt.h>
#include "data.hpp"
#include "interrupt_mutex.hpp"
#ifndef UART_QSIZE
#define UART_QSIZE 100
#endif

/*
void set7seg(uint8_t m_digit);
#include "seg7.h"
*/
class uart:public IO_process{
	public:
	static_queue<uint8_t,UART_QSIZE > Q;
	private:
	uart(){}
	uart(const uart &){}
	uart(uart &&){}
	
	bool transmit_process_on = 0;
	public:
	//inline uint8_t queue_len()const {return Q.len;}
	
	inline void transmit_act(){
		if(Q.is_empty()){
			transmit_process_on = 0;
		}
		else{
			if(transmit_process_on)
				UDR0 = Q.pop();
		}
	}
	private:
	inline void enable_transmit(){
		if(!transmit_process_on){
			transmit_process_on = 1;
			if(UCSR0A & (1<<UDRE0)){
				//PORTB = ~PORTB;
				transmit_act();
			}
		}
	}
	
	public:
	
	static uart & uart_process_r(){
		static uart U;
		return U;
	}
	static uart * uart_process_p(){
		return &uart_process_r();
	}
	
	static constexpr uint16_t defineUBBRn(uint32_t speed, bool double_speed){
		return ((double_speed+1)*F_CPU)/16 - 1;
	}
	void open(uint16_t UBBRn = 16,bool double_speed = true){
		UBRR0H = (unsigned char)(UBBRn>>8);
		UBRR0L = (unsigned char)UBBRn;
		
		// UCSRnA:
		
		if(double_speed){
			UCSR0A |= (1<<U2X0); // удвоение скорости
		}
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
	void close(){
		UBRR0H = 0;
		UBRR0L = 0;
		UCSR0A = 0;
		UCSR0B = 0;
		UCSR0C = 0;
	}

	
	bool write(uint8_t c){
		INTERRUPT_LOCK
		cli();
		if(Q.is_full()){
			INTERRUPT_UNLOCK
			return false;
		}
		else{
			//cli();
			Q.push(c);
			//sei();
			enable_transmit();
			
			INTERRUPT_UNLOCK
			return true;
		}
	}
	bool write(uint8_t buff_size,const uint8_t * buff){
		INTERRUPT_LOCK
		cli();
		if(Q.size() - Q.len < buff_size){
			INTERRUPT_UNLOCK
			return false;
		}
		else{
			//cli();
			for(uint8_t i =0;i < buff_size;++i){
				Q.push(buff[i]);
			}
			//sei();
			enable_transmit();
			INTERRUPT_UNLOCK
			return true;
		}
	}
	bool write(const char* buff){
		INTERRUPT_LOCK
		while (*buff){
			if(!write(*buff)){
				INTERRUPT_UNLOCK
				return false;
			}
			buff++;
		}
		INTERRUPT_UNLOCK
		return true;
	}
	
	slot inline void data_recieve_interrupt(uint8_t data);
	//recievebu
	
};

#define STATIC_UART_CONNECTION(code) ISR(USART_RX_vect){code;}

//transmit
ISR (USART_TX_vect){
	uart::uart_process_r().transmit_act();
}



#endif