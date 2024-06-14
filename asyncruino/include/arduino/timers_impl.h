#pragma once
#include "../core/simple_timer.h"
#include <stdlib.h>
#include <stdint.h>

#ifdef __AVR_ATmega328P__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#endif

#ifdef F_CPU
#define _ARUINO_F_CPU_IN f_cpu = F_CPU
#else
#define _ARUINO_F_CPU_IN f_cpu
#endif

namespace asyncruino{
    
    struct  timer_0_hw__impl{
        static constexpr uint8_t prescal_degs[5] = {0,3,6,8,10};
        private:
        timer_0_hw__impl(){}
        public:
        static timer_0_hw__impl & instance(){
            static timer_0_hw__impl inst;
            return inst;
        }
        constexpr static uint32_t prescalers(uint8_t prescaler_id = 0){
            return prescal_degs[prescaler_id];
        } 
        static void start(uint8_t prescaler_id = 4){
            TCCR0B =  (prescaler_id+1)&0b0000111;
			TCCR0A = (1<<WGM00 | 1<<WGM01);
			TIMSK0 |= 1<<TOIE0;
			TCNT0 = 0;
        }
		static void stop(){
			TIMSK0 &= ~(1<<TOIE0);
		}

        template <typename ret_type,int _pref>
        inline static ret_type ticks_per_prefix_sec(
                time_prefix_t<_pref>,
                uint32_t _ARUINO_F_CPU_IN
            ){
            uint8_t deg_item = (TCCR0B&0b0000111) - 1; 
            constexpr int8_t base_diff = (int8_t)_pref - (int8_t)time_prefix::s;
            constexpr ret_type pow_10 = pow(10.0,base_diff);

            return (pow_10*f_cpu)/( ((uint32_t)1) << (prescal_degs[deg_item]+8)  );
        }

        template <typename ret_type,int _pref>
        inline static ret_type prefix_sec_per_ticks(time_prefix_t<_pref>,uint32_t _ARUINO_F_CPU_IN){
            constexpr int8_t base_diff = (int8_t)time_prefix::s - (int8_t)_pref;
            constexpr ret_type pow_10 = pow(10.0,base_diff);
			uint8_t deg_item = (TCCR0B&0b0000111) - 1; 
            return (pow_10 * ( ((uint32_t)1) << (prescal_degs[deg_item]+8)))/f_cpu;
        }
    };
};
