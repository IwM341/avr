#ifndef SPI_PROCESS_HPP
#define SPI_PROCESS_HPP

#include "io_process.hpp"

class spi:IO_process{
	private:
	spi(){}
	spi(const uart &){}
	spi(uart &&){}
	bool transmit_process_on = 0;
	
	void transmit_act(){
		if(Q.is_empty()){
			transmit_process_on = 0;
		}
		else if(transmit_process_on){
			/*UDR0 = Q.pop(); push register*/
		}
	}
	void enable_transmit(){
		
		if(!transmit_process_on){
			transmit_process_on = 1;
			if(/*UCSR0A & (1<<UDRE0)*/){
				transmit_act();
			}
		}
		
	}
	
	public:
	
	static spi & spi_process_r(){
		static spi S;
		return S;
	}
	static spi * spi_process_p(){
		return &spi_process_r();
	}
};


static spi &SPI = spi::spi_process_r();

//recieve
ISR(SPI_MISO_vect){
	SPI.data_recieve_interrupt(UDR0);
}


//transmit
ISR (SPI_MOSI_vect){
	SPI.transmit_act();
}

#endif