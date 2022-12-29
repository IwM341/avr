#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // указываем пины rx и tx соответственно

void setup()  {
  pinMode(0,INPUT);
  pinMode(1,OUTPUT);
  Serial.begin(115200);
  mySerial.begin(38400);
  Serial.println("start prog 38400");
}

const int baud[] = {1200,2400,4800,9600,19200,38400,57600,115200,230400};
const char*baud_str[] = {"1200","2400","4800","9600","19200","38400","57600","115200","230400"};

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read(); // читаем из software-порта
    Serial.print(c); // пишем в hardware-порт
  }
  if (Serial.available()) {
    char c = Serial.read(); // читаем из hardware-порта
    if(c <='9' && c>='0'){
      mySerial.begin(baud[c-'0']);
      Serial.print("change baud to ");
      Serial.println(baud_str[c-'0']);
    }
    else
      mySerial.write(c); // пишем в software-порт
  }
}
