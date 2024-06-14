#ifndef INTERRUPT_DEBUG_H
#define INTERRUPT_DEBUG_H

#include "../avr_tools/include/guard.h"
//#include "../avr_tools/include/size_types.h"
//#include "../avr_tools/include/micro_set.h"
//#include "../avr_tools/include/timer.h"
//#include "../avr_tools/include/event_loop.h"
//#include "../avr_tools/include/signals.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>

#ifdef _WIN32
    #define SIGALRM SIGINT
    void alarm(int){
        std::cout << "Can't use unix alarms" <<std::endl;
    }
#endif
void default_interrupt(int info){}

static void(*interrupt_processor)(int) = default_interrupt;


void interrupt(int ){
    static int tick = 0;
    //std::cout << "process interrupt, SREG = " <<std::bitset<8>(SREG) <<std::endl; 
    if(SREG){
        std::cout << "TICK "<< tick <<std::endl; 
        ++tick;
        int iinfo;
        //std::cout << "input interrupt id" << std::endl;
        //std::cin >>  iinfo;
        cli();
        interrupt_processor(iinfo);
        sei();
    }
    alarm(1);
}

void init_alarm(){
    signal(SIGALRM,interrupt); // Register signal handle
    alarm(1);
}

#endif//INTERRUPT_DEBUG_H