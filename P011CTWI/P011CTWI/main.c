/*
 * P011CTWI.c
 *
 * Created: 20.07.2022 15:35:24
 * Author : MainUser
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "bmp180.h"



void USART_Init( unsigned int UBBRn)//Инициализация модуля USART
{
	UBRR0H = (unsigned char)(UBBRn>>8);
	UBRR0L = (unsigned char)UBBRn;
	
	// UCSRnA:
	//UCSR0A |= (1<<U2X0); // удвоение скорости
	//
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

void USART_send_byte(uint8_t data){
	uint8_t prsc = 128;
	for(uint8_t i=0;i<8;++i){
		uint8_t rm = (data / prsc) % 2;
		data %= prsc;
		prsc /= 2;
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '0' + rm;
	}
	
}
void USART_send_uint8_t(uint8_t data){
	uint8_t dig;
	dig = data / 100;
	if(dig){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '0' + dig;
	}
	data = data % 100;
	dig = data / 10;
	if(dig){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '0' + dig;
	}
	data = data % 10;
	
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = '0' + dig;
	
}
ISR(USART_RX_vect){
	USART_send(UDR0);
}
ISR(USART_TX_vect){
	
}


//F_TWI = F_CPU/(16 + 2*TWBR*PRESCALAR)
//PRESCALAR = 4^TWPS[1:0] 
//TWPS[1:0]  = TWSR[1:0]
void TWI_init(uint8_t mTWBR/* = 0x20*/,uint8_t mTWPS /*= 0*/){
	mTWPS %= 4;
	TWBR = mTWBR;
	TWSR |= mTWPS;
}
void TWI_StartCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
}
void TWI_StopCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
void TWI_SendByte(unsigned char c)
{
	TWDR = c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}

#define UNUSE(x) ((void)(x))
int main(void)
{
	sei();

    USART_Init(8);//Baud = F_CPU/(16(UBBRn + 1))
	
	_delay_ms(1000);
	USART_send('h');
	USART_send('e');
	USART_send('l');
	USART_send('l');
	USART_send('o');
	USART_send('w');
	USART_send('\n');
	_delay_ms(1000);
	
	Bmp180CalibrationData calibrationData;
	
	while(1)
	{
		uint8_t result = bmp180ReadCalibrationData(&calibrationData);
		
		if (result == BMP180_OK) {
			Bmp180Data bmp180Data;
			USART_send('o');
			USART_send('k');
			USART_send('0');
			USART_send('\n');
			result = bmp180ReadData(BMP180_OSS_STANDARD, &bmp180Data, &calibrationData);
			
			if (result == BMP180_OK) {
				uint8_t temp= bmp180Data.temperatureC;
				long pressure = bmp180Data.pressurePa;
				UNUSE(pressure);
				USART_send('t');
				USART_send_uint8_t(temp);
				USART_send('C');
				} else {
				USART_send('e');
				USART_send('r');
				USART_send('r');
				USART_send('o');
				USART_send('w');
				USART_send(' ');
				USART_send_uint8_t(result);
				USART_send('\n');
			}
			} else {
			USART_send('e');
			USART_send('r');
			USART_send('0');
			USART_send('\n');
		}
// 		USART_send('\"');
// 		for(uint8_t* it = &calibrationData;it < (uint8_t *)(&calibrationData) + sizeof(calibrationData);++it){
// 			USART_send_uint8_t(*it);
// 			USART_send('.');
// 		}
// 		USART_send('\"');
		_delay_ms(2000);
	}
	
	//USART_send('\n');
	
    while (1) 
    {
		
    }
}

