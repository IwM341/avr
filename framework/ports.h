#ifndef PORTS_H
#define PORTS_H

#define set_port(PORT,mask,val) ( (PORT) = ((PORT) & ~(mask)) | (val&mask) )


#define PIN_PORT_0 PORTD
#define PIN_PORT_1 PORTD
#define PIN_PORT_2 PORTD
#define PIN_PORT_3 PORTD
#define PIN_PORT_4 PORTD
#define PIN_PORT_5 PORTD
#define PIN_PORT_6 PORTD
#define PIN_PORT_7 PORTD

#define PIN_PORT_8 PORTB
#define PIN_PORT_9 PORTB
#define PIN_PORT_10 PORTB
#define PIN_PORT_11 PORTB
#define PIN_PORT_12 PORTB
#define PIN_PORT_13 PORTB

#define PIN_MASK_0 0b00000001
#define PIN_MASK_1 0b00000010
#define PIN_MASK_2 0b00000100
#define PIN_MASK_3 0b00001000
#define PIN_MASK_4 0b00010000
#define PIN_MASK_5 0b00100000
#define PIN_MASK_6 0b01000000
#define PIN_MASK_7 0b10000000

#define PIN_MASK_8 0b00000001
#define PIN_MASK_9 0b00000010
#define PIN_MASK_10 0b00000100
#define PIN_MASK_11 0b00001000
#define PIN_MASK_12 0b00010000
#define PIN_MASK_13 0b00100000

constexpr uint8_t & getPort(uint8_t pin){
    return (pin < 8 ? PORTD : (pin < 14 ? PORTB : *((uint8_t *)NULL)  ));
}
constexpr uint8_t getMask(uint8_t pin){
    return (pin < 8 ? 1<<pin : (pin < 14 ? 1<<pin-8 : 0));
}


template <uint8_t pin>
struct PortInfo{
    constexpr static uint8_t & port = getPort(pinNum);
    constexpr static uint8_t mask = getMask(pinNum);
};

#endif