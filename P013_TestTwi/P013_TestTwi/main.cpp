/*
 * P013_TestTwi.cpp
 *
 * Created: 25.07.2022 6:21:01
 * Author : MainUser
 */ 

#include <avr/io.h>

#define  F_CPU 16000000UL
#include <ports.h>
#include <data.hpp>
#include "uart_process.hpp"
#include <avr/interrupt.h>
#include "uart_debugger.hpp"
#include "util/delay.h"
#include "i2c.h"

#include "bmp180/bmp180.h"

STATIC_UART_CONNECTION(/*uart::uart_process_r().write(UDR0)*/)

int main(void)
{
	sei();
	i2c_hardware m_i2c;
	m_i2c.init();
	
	uart::uart_process_r().open(16,true);
    
	bmp180 det1(&m_i2c);
	
	det1.readCalibrationData();
	det1.updateTemperature();
	

	//cout << "press= " << (uint16_t)det1.m_data.temperatureC <<end;
	
	while (1) 
    {
		_delay_ms(4000);
		uint8_t res = det1.updateTemperature();
		if(res == BMP180_OK){
		cli();
		cout << "float temp = " << det1.m_data.temperatureC <<endl;
		cout << "int temp = " << (uint16_t)det1.m_data.temperatureC <<endl;
		
		
		uint16_t c = uart::uart_process_r().Q.start;
		for(uint8_t i = 0;i<uart::uart_process_r().Q.len;++i){
			if(!uart::uart_process_r().Q.buff[c + i]){
				cout << "q contatins zero" <<endl;
				break;
			}
		}
		
		sei();
		//uart::uart_process_r().write("temp = ") <<
		}
		else{
		cout << "error bmp180" << endl;
		}
		
	}
}

