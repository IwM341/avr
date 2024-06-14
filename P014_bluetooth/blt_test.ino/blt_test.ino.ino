#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // указываем пины rx и tx соответственно

int bauds[] = {9600, 14400, 19200, 38400, 57600, 115200, 128000, 256000};
uint8_t bn = 0;
constexpr uint8_t size = sizeof(bauds)/sizeof(int);
void setup()  {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(38400);
  mySerial.begin(bauds[bn]);
  Serial.println("start prg");
}

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read(); // читаем из software-порта
    
    Serial.print(c); // пишем в hardware-порт
  }
  if (Serial.available()) {
    char c = Serial.read(); // читаем из hardware-порта
    if(c == '+'){
      if(bn < size-1){
        ++bn;
        mySerial.begin(bauds[bn]);
        Serial.println("set baud");
      }
    }
    else if(c == '-'){
      if(bn >0){
        --bn;
        mySerial.begin(bauds[bn]);
        Serial.println("set baud");
      }
    }
    else
      mySerial.write(c); // пишем в software-порт
  }
}
