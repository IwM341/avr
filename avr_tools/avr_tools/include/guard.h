/*
 * guard.h
 *
 * Created: 08.04.2023 16:45:29
 *  Author: MainUser
 */ 


#ifndef GUARD_H_
#define GUARD_H_


#ifdef __AVR_ATmega328P__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>
#else
#include <mutex>
static volatile uint8_t SREG = 0;
#define cli() (SREG = 0)
#define sei() (SREG = (1<<7)) 
#endif

namespace aos{
	/**
	\brief standart guard, which disables interrupts after lock, and enables after unlock
	*/
	struct __guard{
		uint8_t sreg;
		inline  void lock(){
			if(SREG&0x80){// 0b1000 0000
				sreg = SREG;
				cli();
			}else
				sreg = SREG;
			
		}
		inline  void unlock(){
			SREG = sreg;
		}
	};
	struct spin_blocker{
		
		bool _is_locked;
		
		spin_blocker():_is_locked(0){}
		inline bool locked(){return _is_locked;}
		
		inline  void lock(){
			uint8_t sreg = SREG;
			cli();
			if(_is_locked){
				SREG = sreg;
				while(!_is_locked);
			}
			_is_locked = 1;
			SREG = sreg;
		}
		inline  void unlock(){
			uint8_t sreg = SREG;
			cli();
			_is_locked = 0;
			SREG = sreg;
		}
	};
	
	/**
	\brief guard, which do nothing
	*/
	struct no_guard{
		inline  void lock(){}
		inline  void unlock(){}
	};
	
	/**
	\brief class, which locks guard in constructor and unlocks in destructor
	*/
	template <typename guard>
	struct lock_guard{
		guard & m;
		inline  explicit lock_guard(guard & m):m(m){m.lock();}
		inline  ~lock_guard(){m.unlock();}
	};
	
	struct lock_interrpupts{
		uint8_t sreg;
		inline  lock_interrpupts(){
			sreg = SREG;
			cli();
		}
		inline  ~lock_interrpupts(){
			SREG = sreg;
		}
	};
}


#endif /* GUARD_H_ */