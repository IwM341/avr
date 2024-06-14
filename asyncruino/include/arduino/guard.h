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
#define __TESTING_ON_OS__
#include <mutex>
#endif

#ifdef ASYNCRUINO_DOUBLE_LOCK_DEBUG
void double_locked(void);
void double_unlocked(void);
#endif
namespace asyncruino{
	#ifdef __TESTING_ON_OS__
	typedef std::mutex default_guard;
	#else

	
	

	struct default_guard{
		inline default_guard(){
			#ifdef ASYNCRUINO_DOUBLE_LOCK_DEBUG
			locked = false;
			#endif
		}
		uint8_t sreg;

		#ifdef ASYNCRUINO_DOUBLE_LOCK_DEBUG
		bool locked;
		#endif
		
		
		inline void lock(){
			uint8_t sreg_tmp = SREG;
			cli();
			sreg = sreg_tmp;
			#ifdef ASYNCRUINO_DOUBLE_LOCK_DEBUG
			if(locked){
				double_locked();
			}
			locked = true;
			#endif
			
		}
		inline void unlock(){
			#ifdef ASYNCRUINO_DOUBLE_LOCK_DEBUG
			if(!locked){
				double_unlocked();
			}
			locked = false;
			#endif
			SREG = sreg;
		}
	};
	#endif
};
#endif /* GUARD_H_ */