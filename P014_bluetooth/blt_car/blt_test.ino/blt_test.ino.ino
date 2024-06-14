#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  // указываем пины rx и tx соответственно

struct SimpleMotor {
  uint8_t pin_forward, pin_back;
  SimpleMotor(uint8_t pin_forward, uint8_t pin_back)
    : pin_forward(pin_forward), pin_back(pin_back) {
    pinMode(pin_forward, OUTPUT);
    pinMode(pin_back, OUTPUT);
    go(0);
  }
  ~SimpleMotor() {
    pinMode(pin_forward, INPUT);
    pinMode(pin_back, INPUT);
  }

  void go(int8_t direction) {
    if (direction > 0) {
      digitalWrite(pin_back, LOW);
      digitalWrite(pin_forward, HIGH);
    } else if (direction < 0) {
      digitalWrite(pin_forward, LOW);
      digitalWrite(pin_back, HIGH);
    } else {
      digitalWrite(pin_forward, LOW);
      digitalWrite(pin_back, LOW);
    }
  }
};
main struct signed_idempotent {
  int8_t value;

  constexpr static int8_t sign(int8_t x) {
    return (x > 0 ? 1 : (x < 0 ? -1 : 0));
  }

  signed_idempotent(int8_t value = 0)
    : value(sign(value)) {}
  inline signed_idempotent& operator++() {
    if (value > 0)
      return *this;
    else
      ++value;
    return *this;
  }
  inline signed_idempotent& operator--() {
    if (value < 0)
      return *this;
    else
      --value;
    return *this;
  }
  inline operator int8_t&() {
    return value;
  }
  inline operator int8_t const&() const {
    return value;
  }
};


SimpleMotor Motor(2, 3);
SimpleMotor Turn(4, 5);
signed_idempotent f_s;
signed_idempotent t_s;

void setup() {
  Serial.begin(9600);
  Serial.println("setup uart");
}

void loop() {


  if (Serial.available()) {
    char c = Serial.read();  // читаем из hardware-порта
    if (c == 'w') {
      ++f_s;
      Motor.go(f_s);
    } else if (c == 's') {
      --f_s;
      Motor.go(f_s);
    } else if (c == 'd') {
      ++t_s;
      Turn.go(t_s);
    } else if (c == 'a') {
      --t_s;
      Turn.go(t_s);
    }
    Serial.print("go with vector(");
    Serial.print(f_s);
    Serial.print(", ");
    Serial.print(t_s);
    Serial.println(")");
  }
}
