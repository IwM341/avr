#pragma once
#include "stdint.h"
#include <cstdlib>

struct water_every_item{
    bool exist_flag;
    uint_least8_t days_delay;
    uint_least8_t tmp_delayed_days;
    uint_least8_t hh,mm,ss;

    inline void destroy(){
        exist_flag = false;
    }
    inline void construct(){
        exist_flag = true;
    }
    inline void set_time(
        uint_least8_t _hh,uint_least8_t _mm,
        uint_least8_t _ss,uint_least8_t _days_delay = 1)
    {
        construct();
        hh=_hh;
        mm=_mm;
        ss=_ss;
        days_delay = _days_delay > 0 ? _days_delay : 1;
        tmp_delayed_days = 0;
    }
    void next_day(){
        tmp_delayed_days++;
    }
    bool is_ready(uint_least8_t tmp_hh,uint_least8_t tmp_mm,uint_least8_t tmp_ss){
        if(tmp_delayed_days < days_delay){
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
        tmp_delayed_days = 0;
    }
};