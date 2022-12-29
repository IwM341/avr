/*
 * GccApplication3.cpp
 *
 * Created: 26.12.2022 11:53:47
 * Author : Artem
 */ 

#include <avr/io.h>



#include <FreeRTOS.h>
#include <task.h>
#include <ports.h>


void Blink10(void *);
void Blink11(void *);
int main(void)
{
	//DDRD = 0x00;
	DDRD |= (PIN_MASK_2 | PIN_MASK_3);
	PORTD = 0xFF;
	
	xTaskCreate(Blink10,NULL,128,NULL,2,NULL);
	xTaskCreate(Blink11,NULL,128,NULL,2,NULL);
	vTaskStartScheduler();
	while(1){}
	
}

void Blink10(void *){
	
	const int delayTime = 1000 / portTICK_PERIOD_MS;
	
	while(1){
		vTaskSuspendAll();
		set_port(PIN_PORT_2,PIN_MASK_2,0xFF);
		xTaskResumeAll();
		
		vTaskDelay(delayTime);
		
		vTaskSuspendAll();
		set_port(PIN_PORT_2,PIN_MASK_2,0x00);
		xTaskResumeAll();
		
		vTaskDelay(delayTime);
	}
	
}
void Blink11(void *){
	
	const int delayTime = 500 / portTICK_PERIOD_MS;
	
	while(1){
		vTaskSuspendAll();
		set_port(PIN_PORT_3,PIN_MASK_3,0xFF);
		xTaskResumeAll();
	
		vTaskDelay(delayTime);
	
		vTaskSuspendAll();
		set_port(PIN_PORT_3,PIN_MASK_3,0x00);
		xTaskResumeAll();
	
		vTaskDelay(delayTime);
	}
}
