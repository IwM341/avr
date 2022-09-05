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
	TCCR1B = (1<<WGM12) | (1<<CS12); // ������������� ����� ��� (����� �� ����������)
	TIMSK1 = (1<<OCIE1A);	//������������� ��� ���������� ���������� 1��� �������� �� ���������� � OCR1A(H � L)
	OCR1AH = (unsigned char)(mOCRA>>8); //���������� � ������� ����� ��� ���������
	OCR1AL = (unsigned char) mOCRA; //���������� � ������� ����� ��� ���������
	//TCCR1B |= (1<<CS12);//��������� ��������.
}

void USART_send(uint8_t data);
char c = 's';
ISR (TIMER1_COMPA_vect) //���� ����������
{
	USART_send(c);
	//USART_send('\n');
	c = 'c';
}

void USART_Init( unsigned int UBBRn)//������������� ������ USART
{
	UBRR0H = (unsigned char)(UBBRn>>8);
	UBRR0L = (unsigned char)UBBRn;
	
	// UCSRnA:
	//UCSR0A |= (1<<U2X0); // �������� ��������
	
	// UCSRnB:
	UCSR0B = (1<<RXEN0)|( 1<<TXEN0); //�������� ����� � �������� �� USART
	UCSR0B |= (1<<RXCIE0) | (1<<TXCIE0); //��������� ���������� ���  ������ � ��������
	//UCSZn2 = 1 ��� 9 ���
	
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);// ���������� ������ � �������� UCSRnC,
	//USBS0 = 1 - 2 ����-����
	//UMSELn - ����������/�����������
	//1 ����-��� (USBS=0), 8-��� ������� (UCSZ1=1 � UCSZ0=1)
	//UCSRC |= (1<<UPMn1);//��������
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

