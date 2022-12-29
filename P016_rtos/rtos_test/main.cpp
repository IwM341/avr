/*
 * rtos_example.cpp
 *
 * Created: 25.12.2022 21:55:41
 * Author : Artem
 */ 

#include <avr/io.h>
#include <Arduino_FreeRTOS.h>
#include <ports.h>
void Blink10(void *);
void Blink11(void *);
int main(void)
{
	DDRD = 0x00;
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	xTaskCreate(Blink10,NULL,128,NULL,2,NULL);
	xTaskCreate(Blink11,NULL,128,NULL,2,NULL);
    while(1){
	}
	
}

void Blink10(void *){
	set_port(PORTB,0x0001000,0xFF);
	vTaskDelay(100);
	set_port(PORTB,0x0001000,0x00);
	vTaskDelay(100);
}
void Blink11(void *){
	set_port(PORTB,0x0000100,0xFF);
	vTaskDelay(80);
	set_port(PORTB,0x0000100,0x00);
	vTaskDelay(80);
}