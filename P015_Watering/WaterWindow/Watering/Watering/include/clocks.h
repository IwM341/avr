#pragma once
#include "stdint.h"
#include "data_time.h"
#include <cstdlib>
struct Clocks : public hh_mm_ss_dd{
    inline Clocks():hh_mm_ss_dd(0,0,0,0),
    _inday_counter(0),_tacts_per_count(1),_f_cpu(1){}

    private:
    uint_least64_t _inday_counter;
    uint_least32_t _tacts_per_count;
    uint_least32_t _f_cpu;
    //
    uint_least64_t _d_counts;
    uint_least64_t _hh_counts;
    uint_least32_t _mm_counts;
    uint_least32_t _ss_counts;


    inline void _update_counts(){
        constexpr uint_least32_t min_sec = 60;
        constexpr uint_least64_t hour_sec = 60*60;
        constexpr uint_least64_t day_sec = 60*60*24;
        _ss_counts = _f_cpu/_tacts_per_count;
        _mm_counts = (_f_cpu*min_sec)/_tacts_per_count;
        _hh_counts = (_f_cpu*hour_sec)/_tacts_per_count;
        _d_counts = (_f_cpu*day_sec)/_tacts_per_count;
    }

    public:
    inline void set_tacts_per_count(uint_least32_t new_tacts_per_count){
        _tacts_per_count = new_tacts_per_count; 
        _update_counts();
    }
    inline void set_f_cpu(uint_least32_t new_f_cpu){
        _f_cpu = new_f_cpu; 
        _update_counts();
    }
    inline void set_time(uint_least8_t n_hh, uint_least8_t n_mm,uint_least8_t n_ss){
        if(n_hh >= 24) 
            n_hh = 23;
        if(n_mm >= 60) 
            n_mm = 59;
        if(n_ss >= 60) 
            n_ss = 59;
        hh = n_hh;
        mm = n_mm;
        ss = n_ss;
        uint_fast64_t m_secs = (uint_fast64_t)days*(24*60*60) + hh*3600+mm*60+ss;
        _inday_counter = (m_secs*_f_cpu)/_tacts_per_count;
        update();
    }

    inline void tick(){
        ++_inday_counter;
    }
	inline void tick(uint_least32_t delta_counter){
		_inday_counter+=delta_counter;
		update();
	}
	
	
    inline void update(){
        while(_inday_counter >=  _d_counts){
            _inday_counter -= _d_counts;
            days += 1;
        }
        hh = _inday_counter/_hh_counts;
        uint_least32_t _inday_minut_counter = _inday_counter%_hh_counts;
        if(hh >= 24)
            hh = 23;
        mm = _inday_minut_counter/_mm_counts;
        uint_least32_t _inday_sec_counter = _inday_minut_counter%_mm_counts;
        if(mm >= 60)
            mm = 59;
        ss = (_inday_sec_counter*_tacts_per_count)/_f_cpu;
        if(ss >= 60)
            ss = 59;
    }
};
// open 1 Temp