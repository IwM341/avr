#pragma once
#include <stdint.h>
#ifdef __AVR_ATmega328P__
#include <avr/eeprom.h>
#endif

struct Settings{
    //Temeratures
    float T1o; // open 1 Temp
    float T1c; //close 1 Temp
    float T2o; // open 2 Temp
    float T2c; //close 2 Temp
    //Times
    float Tmd; // min delay time (seconds)
    float Twd; // water continue time (seconds)
    
    //internal clock parameter
    uint_least32_t f_cpu; // actual _f_cpu in Hz

    
    void set_default(){
        T1o = 28;
        T1c = 27;
        T2o = 28;
        T2c = 27;

        Tmd = 3600.0*24;
        Twd = 60;
        f_cpu = 16000000UL;
    }
    static Settings load(){
        Settings S;
        #ifdef __AVR_ATmega328P__
        eeprom_read_block((void *)&S,NULL,sizeof(Settings));
        #endif
        if(S.f_cpu < 7000000UL || S.f_cpu > 20000000UL){
            S.set_default();
        }
        return S;
    }
    void save()const{
        #ifdef __AVR_ATmega328P__
        eeprom_update_block(this,NULL,sizeof(Settings));
        #endif
    }
    
};

