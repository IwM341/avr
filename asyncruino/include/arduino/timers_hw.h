#pragma once
#include "../core/simple_timer.h"
#include "timers_impl.h"
#include "scheduler.h"
#include "guard.h"

#ifdef __AVR_ATmega328P__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#endif


#define ASYNCRUINO_TIMER0_ENABLE

#ifdef ASYNCRUINO_TIMER0_ENABLE


#ifndef ASYNCRUINO_TIMER0_TIME_T
#define ASYNCRUINO_TIMER0_TIME_T uint32_t
#endif

#ifndef ASYNCRUINO_TIMER0_DIVIDER_T
#define ASYNCRUINO_TIMER0_DIVIDER_T float
#endif

#ifndef ASYNCRUINO_TIMER0_PREFIX
#define ASYNCRUINO_TIMER0_PREFIX s
#endif

#ifndef ASYNCRUINO_TIMER0_MAX_LISTENERS
#define ASYNCRUINO_TIMER0_MAX_LISTENERS 16
#endif

#endif


namespace asyncruino
{
    namespace tl = time_literals;

    template <
        typename time_t = uint32_t,
        uint8_t max_listeners = 16,
        typename div_t = uint32_t,
	 	int8_t prefix = ::asyncruino::time_prefix::s
    >
    using timer_counter_t = 
        timer_counter_impl<
            scheduler,default_guard,time_t,
            timer_dim_counter<uint64_t,div_t,prefix>,
            uint8_t,max_listeners>;
    
	typedef timer_counter_t<
		ASYNCRUINO_TIMER0_TIME_T,
		ASYNCRUINO_TIMER0_MAX_LISTENERS,
		ASYNCRUINO_TIMER0_DIVIDER_T,
		::asyncruino::time_prefix::s
	>  timer0_impl_t;
	
    #ifdef ASYNCRUINO_TIMER0_ENABLE 
    struct timer0:public timer0_impl_t {
        
	private:
		timer0():timer0_impl_t(scheduler::instance(),0){
			#ifdef F_CPU
			set_speed(F_CPU);
			#endif
		}
	public:
		void set_speed(uint32_t _ARUINO_F_CPU_IN){
			timer_0_hw__impl::start(4);
			auto _pspt = timer_0_hw__impl::instance().
				prefix_sec_per_ticks<ASYNCRUINO_TIMER0_DIVIDER_T>(tl::s,f_cpu);
			this->timer0_impl_t::set_speed(_pspt,tl::s);
		}
		static timer0 & instance(){
			static timer0 m_inst;
			return m_inst;
		}
		
		
    };
	
	ISR(TIMER0_OVF_vect){
		timer0::instance().interrupt();
	}
	
    #endif
    

}  // namespace asyncruino
