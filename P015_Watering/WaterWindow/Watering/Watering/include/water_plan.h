#pragma once
#include "stdint.h"
#include "data_time.h"

struct WaterPlanItem {
    bool actual;
	bool force;
    hh_mm_ss_dd ptime;
	uint32_t duration;
    
    inline void set_time(
		uint32_t _duration,
        uint_least8_t _hh,uint_least8_t _mm,
        uint_least8_t _ss,uint_least8_t _days_delay = 0)
    {
        actual = false;
		force = false;
		duration = _duration;
        ptime.hh=_hh;
        ptime.mm=_mm;
        ptime.ss=_ss;
        ptime.days= _days_delay;
    }
    void next_day(){
        if(ptime.days > 0)
            ptime.days--;
    }

    bool is_ready(uint_least8_t tmp_hh,uint_least8_t tmp_mm,uint_least8_t tmp_ss){
        if(ptime.days > 0){
            return false;
        }
        if(ptime.hh > tmp_hh){
            return false;
        } else if (ptime.hh < tmp_hh ) {
            return true;
        }

        if(ptime.mm > tmp_mm){
            return false;
        } else if (ptime.mm < tmp_mm) {
            return true;
        }
        return tmp_ss >= ptime.ss;
    }
    void after_water(){
        actual = false;
    }
};