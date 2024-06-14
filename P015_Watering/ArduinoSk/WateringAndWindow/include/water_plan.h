#pragma once
#include "stdint.h"
#include <cstdlib>

struct water_plan {
    bool actual;
    uint_least8_t hh,mm,ss;
    uint_least8_t tmp_days_remain;
    
    inline void set_time(
        uint_least8_t _hh,uint_least8_t _mm,
        uint_least8_t _ss,uint_least8_t _days_delay = 0)
    {
        actual = true;
        hh=_hh;
        mm=_mm;
        ss=_ss;
        tmp_days_remain = _days_delay;
    }
    void next_day(){
        if(tmp_days_remain > 0)
            tmp_days_remain--;
    }

    bool is_ready(uint_least8_t tmp_hh,uint_least8_t tmp_mm,uint_least8_t tmp_ss){
        if(tmp_days_remain > 0){
            return false;
        }
        if(hh > tmp_hh){
            return false;
        } else if (hh < tmp_hh ) {
            return true;
        }

        if(mm > tmp_mm){
            return false;
        } else if (mm < tmp_mm) {
            return true;
        }
        return tmp_ss >= ss;
    }
    void after_water(){
        actual = false;
    }
};