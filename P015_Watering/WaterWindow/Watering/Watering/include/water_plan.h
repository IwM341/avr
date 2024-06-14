#pragma once
#include "stdint.h"
#include "data_time.h"
#include <cstdlib>

struct water_plan {
    bool actual;
    hh_mm_ss_dd m_time;
    
    inline void set_time(
        uint_least8_t _hh,uint_least8_t _mm,
        uint_least8_t _ss,uint_least8_t _days_delay = 0)
    {
        actual = true;
        m_time.hh=_hh;
        m_time.mm=_mm;
        m_time.ss=_ss;
        m_time.days= _days_delay;
    }
    void next_day(){
        if(m_time.days > 0)
            m_time.days--;
    }

    bool is_ready(uint_least8_t tmp_hh,uint_least8_t tmp_mm,uint_least8_t tmp_ss){
        if(m_time.days > 0){
            return false;
        }
        if(m_time.hh > tmp_hh){
            return false;
        } else if (m_time.hh < tmp_hh ) {
            return true;
        }

        if(m_time.mm > tmp_mm){
            return false;
        } else if (m_time.mm < tmp_mm) {
            return true;
        }
        return tmp_ss >= m_time.ss;
    }
    void after_water(){
        actual = false;
    }
};