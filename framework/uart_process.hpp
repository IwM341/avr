#ifndef UART_PROCESS_HPP
#define UART_PROCESS_HPP

#include "io_process.hpp"
#include <avr/interrupt.h>


#ifndef UART_QSIZE
#define UART_QSIZE 128
#endif

class uart:public IO_process{
	private:
	static_queue<uint8_t,UART_QSIZE > Q;
	uart(){}
	uart(const uart &){}
	uart(uart &&){}
	
	bool transmit_process_on = 0;
	public:
	void transmit_act(){
		if(Q.is_empty()){
			transmit_process_on = 0;
		}
		else if(transmit_process_on){
			UDR0 = Q.pop();
		}
	}
	private:
	void enable_transmit(){
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
		return ((double_speed+1)*F_CPU)/16- 1;
	}
	void open(uint16_t UBBRn = 16,bool double_speed = false){
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
		if(Q.is_full()){
			return false;
		}
		else{
			Q.push(c);
			enable_transmit();
		}
	}
	bool write(uint8_t buff_size,const uint8_t * buff){
		if(Q.size() - Q.len < buff_size){
			return false;
		}
		else{
			for(uint8_t i =0;i < buff_size;++i){
				Q.push(buff[i]);
			}
			enable_transmit();
		}
	}
	slot inline void data_recieve_interrupt(uint8_t data);
	//recieve
	
};

ISR (USART_RX_vect){
	uart::uart_process_r().data_recieve_interrupt(UDR0);
}


//transmit
ISR (USART_TX_vect){
	uart::uart_process_r().transmit_act();
}



#endif