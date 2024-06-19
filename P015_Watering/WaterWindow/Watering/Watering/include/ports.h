#ifndef PORTS_H
#define PORTS_H
#include <stdint.h>
#include "type_traits.h"

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

inline void set_port_bit(volatile uint8_t & _port,uint8_t bit_num,uint8_t value){
	if(value){
		_port |= (1<<bit_num);
	} else {
		_port &= ~(1<<bit_num);
	}
}

namespace pins{
	
		
	struct PortB_Tag{
		inline static volatile uint8_t & port()
		{
			return PORTB;
		}
		inline static volatile uint8_t & ddr()
		{
			return DDRB;
		}
	};
	struct PortC_Tag{
		inline static volatile uint8_t & port()
		{
			return PORTC;
		}
		inline static volatile uint8_t & ddr()
		{
			return DDRC;
		}
	};
	struct PortD_Tag{
		inline static volatile uint8_t & port()
		{
			return PORTD;
		}
		inline static volatile uint8_t & ddr()
		{
			return DDRD;
		}
	};
	
	template <uint8_t m_pin>
	inline auto Port_Tag(){
		static_assert(m_pin < 20,"pin > 20, not existing pin");
		return Std::conditional_t<
			(m_pin < 8),
			PortD_Tag,
			Std::conditional_t<
				(m_pin < 14),
				PortB_Tag,
				PortC_Tag
			>
		>{};
	}
	
	template <uint8_t m_pin>
	inline constexpr uint8_t getBit(){
		static_assert(m_pin < 20,"pin > 20, not existing pin");
		return (m_pin < 8) ?
					m_pin:
					(
						(m_pin < 14) ?
							(m_pin-8):
							(m_pin-14)
					);
	}
	
	template <uint8_t m_pin>
	inline constexpr uint8_t getMask(){
		static_assert(m_pin < 20,"pin > 20, not existing pin");
		
		return (m_pin < 8) ? 
					(1 << m_pin):
					(
						(m_pin < 14) ?
							(1<<(m_pin-8)):
							(1<<(m_pin-14))
					);
	}


	struct InputMode_tag{};
	struct OutputMode_tag{};
		
	constexpr static InputMode_tag InputMode = InputMode_tag{};
	constexpr static OutputMode_tag OutputMode = OutputMode_tag{};
	
	
	
	template <uint_least8_t pinNumber>
	struct pin{
		typedef decltype(Port_Tag<pinNumber>()) PinInfo;
		static constexpr uint8_t mask = getMask<pinNumber>();
		static constexpr uint8_t bit_num = getBit<pinNumber>();
		
		template <typename PinMode_t = InputMode_tag>
		inline pin(PinMode_t){
			set_mode(PinMode_t{});
		}
		
		template <typename PinMode_t = InputMode_tag>
		inline void set_mode(PinMode_t){
			if (Std::is_same_v<PinMode_t,OutputMode_tag>){
				set_port_bit(PinInfo::ddr(),bit_num,1);//1 - output
				} else {
				set_port_bit(PinInfo::ddr(),bit_num,0);
			}
		}
		
		inline bool Read() const{
			return ((PinInfo::port() & mask)  != 0);
		}
		inline void Write(bool Value){
			return set_port_bit(PinInfo::port(),bit_num,Value);
		}
		inline void Write_0(){
			return set_port_bit(PinInfo::port(),bit_num,0);
		}
		inline void Write_1(){
			return set_port_bit(PinInfo::port(),bit_num,1);
		}
	};	
};


#endif