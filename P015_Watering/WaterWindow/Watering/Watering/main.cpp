/*
 * Watering.cpp
 *
 * Created: 05.06.2024 17:00:36
 * Author : MainUser
 */ 

#include <avr/io.h>
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "include/ports.h"
#include "../Uart/HardwareSerial.h"
#include "global.h"
#include <avr/interrupt.h>
static void vLEDBlink_task(void *) {
	
		
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

int main(void)
{
	volatile uint32_t x = __cplusplus;
    xTaskCreate(vLEDBlink_task, "LED Blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	for(;;);
	return 0;
}

