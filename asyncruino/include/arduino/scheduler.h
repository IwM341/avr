#pragma once

#include "../core/scheduler.h"
#include "guard.h"

#ifdef __AVR_ATmega328P__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#endif

#ifndef ASYNCRUINO_MAX_TASKS
#define ASYNCRUINO_MAX_TASKS 32
#endif

namespace asyncruino{

    using schd_impl_t = scheduler_impl<default_guard,ASYNCRUINO_MAX_TASKS>;
    struct scheduler:schd_impl_t
    {
        private:
        scheduler(){
			sei();
		}
        public:
        inline static scheduler & instance(){
            static scheduler m_inst;
            return m_inst;
        }
		inline static int run(){
			instance().schd_impl_t::run();
			return -1;
		}
    };
    
};
    

