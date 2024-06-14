//#include <EEPROM.h>

#include <Arduino.h>
//#include <Adafruit_BMP085.h>
#include <Arduino_FreeRTOS.h>
#include <HardwareSerial.cpp>
//#include "include/clocks.h"

//Adafruit_BMP085 Temp_sensor;

void InterfaceProcess(void *);
void WindowProcess(void *);
void WaterProcess(void *);



void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  //Temp_sensor.begin();
}

void loop() {

  Serial.println("temp = ");
  float T = 0;//Temp_sensor.readTemperature();
  Serial.println(T);

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}


