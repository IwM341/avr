#pragma once
#include <stdint.h>


#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include <avr/eeprom.h>
#include "../Uart/HardwareSerial.h"
#include "include/clocks.h"
#include "Pump.h"
#include "avr/interrupt.h"
#include "include/guard.h"

#include "include/water_plan.h"
#include "include/water_every.h"

#define WaterSetPin 16
#define WaterStatusPin 17

#define VccPins 15,8 // pins output is vcc
#define GndPins 6,7  // pins putput is gnd

#define Window0_open_pin 4
#define Window0_close_pin 5
#define Window0_isopen_pin 6
#define Window0_isclosed_pin 7

#define Window1_open_pin 4
#define Window1_close_pin 5
#define Window1_isopen_pin 6
#define Window1_isclosed_pin 7



struct Settings{
    //Temeratures
    float T1o; // open 1 Temp
    float T1c; //close 1 Temp
    float T2o; // open 2 Temp
    float T2c; //close 2 Temp
    //Times
    uint_least32_t Tmd; // min delay time (seconds)
    uint_least32_t Twd; // water continue time (seconds)
    
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
        eeprom_read_block((void *)&S,NULL,sizeof(Settings));
        if(S.f_cpu < 7000000UL || S.f_cpu > 20000000UL){
            S.set_default();
        }
        return S;
    }
    void save()const{
        eeprom_update_block(this,NULL,sizeof(Settings));
    }
    
};


void NextDayUpdatePlans();

extern guarded<float,atomic_guard> Temp;
extern guarded<Settings> settings;
extern guarded<Clocks,guard_timer0> clocks;



typedef Std::array<WaterPlanItem,8> water_plan_array_t;
typedef Std::array<WaterEveryItem,4> water_every_array_t;

extern guarded<water_plan_array_t &> water_plan;
extern guarded<water_every_array_t &> water_every;

typedef Pump<WaterSetPin,WaterStatusPin> Pump_t;
extern Pump_t water_impl;

int_least8_t plan_water(const hh_mm_ss_dd & m_time,int_least32_t duration = -1);
inline int_least8_t plan_water_now(int_least32_t duration = -1){
	return plan_water(clocks.get([](Clocks const & clk){return clk.current();}), duration);
}
int_least8_t shedule_water(const hh_mm_ss_dd & m_time,uint_least8_t days_delay = 1, int_least32_t duration = -1);


