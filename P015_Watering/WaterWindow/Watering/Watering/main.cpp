/*
 * Watering.cpp
 *
 * Created: 05.06.2024 17:00:36
 * Author : MainUser
 */ 

#include <avr/io.h>

#include "include/ports.h"
#include "global.h"
#include <avr/interrupt.h>

void vLEDBlink_task(void *) {
	
		
	pins::pin<7> m_pin(pins::OutputMode);
	
	TickType_t xNextWakeTime = xTaskGetTickCount();
	const int delayTime = 1000;
	Serial.begin(112500);
	for(;;) {
		int tmp_t = xTaskGetTickCount();
		PORTB = ~PORTB;
		vTaskDelayUntil(&xNextWakeTime, delayTime);
		Serial.println('i');
	}
}


void start_clock();

void update_clock(void *);
void task_watering(void *);
void task_window(void *);
void task_command_executor(void *);

int main(void)
{
	xTaskCreate(update_clock,"u",configMINIMAL_STACK_SIZE,NULL,1,NULL);
	xTaskCreate(task_watering, "w", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(task_window, "o", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(task_command_executor, "c", 2*configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	for(;;);
	return 0;
}

