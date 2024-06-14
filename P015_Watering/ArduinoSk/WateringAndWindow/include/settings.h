#pragma once
#include "stdint.h"
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
    uint_least32_t _f_cpu; // actual _f_cpu in Hz
};
// open 1 Temp