#pragma once
#include <stdint.h>

struct hh_mm_ss_dd{
    uint_least8_t hh;
    uint_least8_t mm;
    uint_least8_t ss;
    uint_least32_t days;
    hh_mm_ss_dd(){}
    hh_mm_ss_dd(int_least32_t days,uint_least8_t hh,uint_least8_t mm,uint_least8_t ss = 0):
    hh(hh),mm(mm),ss(ss),days(days){}
};