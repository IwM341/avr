#pragma once
#include "type_traits.h"
#include "string_filter.h"
#include "string_view.h"
#include "data_time.h"

typedef int_least8_t error_pos_t;


template<typename int_t>
error_pos_t parse_int(Std::string_view & S,int_t & value){
    using namespace StrFlt;
    error_pos_t pos = 0;
    while(!S.empty() && space(S.front())){
        S.step();
        ++pos;
    }
    bool is_minus = false;
    if(!S.empty() &&S.front() == '-'){
        is_minus = true;
        ++pos;
        S.step();
    }

    value = 0;
    if(S.empty() || !num(S.front())){
        return pos ? pos : -1;
    }
    while(!S.empty() && num(S.front())){
        value *= 10;
        value += S.front() - '0';
        S.step();
    }
    if(is_minus){
        value = -value;
    }
    return 0;
}

template <typename float_t>
error_pos_t parse_float(Std::string_view & S,float_t  & value){
    using namespace StrFlt;
    error_pos_t pos =0;
    while(!S.empty() && space(S.front())){
        S.step();
        ++pos;
    }

    bool is_minus = false;
    if(!S.empty() &&S.front() == '-'){
        is_minus = true;
        S.step();
        ++pos;
    }
    while(!S.empty() && space(S.front())){
        S.step();
        ++pos;
    }
    if(S.empty()  || (!num(S.front()) && !(S.front() != '.'))){
        return pos;
    }
    value = 0;
    while(!S.empty() && num(S.front())){
        value *= 10;
        value += S.front() - '0';
        S.step();
    }
    if(S.empty() || S.front() != '.'){
        if(is_minus){
            value = -value;
        }
        return 0;
    }

    S.step();
    float_t frac_part = 0;
    float_t degree = 0.1;
    while(!S.empty() && num(S.front())){
        frac_part += (S.front() - '0')*degree;
        degree*= 0.1;
        S.step();
    }
    value += frac_part;
    if(is_minus){
        value = -value;
    }
    return 0;
}


Std::string_view parse_command(Std::string_view & S){
    using namespace StrFlt;
    while(!S.empty() && space(S.front())){
        S.step();
    }
    if(!S.empty() && letter(S.front())){
        const char * begin =  S.begin();
        size_t _size=1;
        S.step();
        while(!S.empty() && letter(S.front())){
            S.step();
            _size++;
        }
        return Std::string_view(begin,_size);
    } 
    return {};
}

Std::string_view parse_variable(Std::string_view & S){
    using namespace StrFlt;
    while(!S.empty() && space(S.front())){
        S.step();
    }
    if(!S.empty() && variable_begin(S.front())){
        const char * begin =  S.begin();
        size_t _size=1;
        S.step();
        while(!S.empty() && variable(S.front())){
            S.step();
            _size++;
        }
        return Std::string_view(begin,_size);
    } 
    return {};
}



error_pos_t parse_hh_mm_dd(Std::string_view & S,hh_mm_ss_dd & date){
    using namespace StrFlt;
    error_pos_t pos = 0;
    date.hh = date.mm = date.ss = date.days = 0;

    while(!S.empty() && space(S.front())){
        S.step();
        ++pos;
    }

    auto read_digit = [&S](auto & m_num)->error_pos_t{
        error_pos_t pos = 0;
        if(!S.empty() && num(S.front())){
            m_num = (S.front()-'0');
            S.step();
            ++pos;
        } else {
            return (pos == 0? -1 : pos);
        } 
        if(!S.empty() && num(S.front())){
            m_num+=m_num*10 + (S.front()-'0');
            S.step();
            ++pos;
        } else if (!S.empty() && S.front() == ':'){
            return 0;
        } else {
            return (pos == 0? -1 : pos);
        }
        return 0;
    };
    {
        auto dpos = read_digit(date.hh);
        if(dpos != 0){
            pos += dpos;
            return (pos == 0 ? -1 : pos) ;
        }
        if(S.empty() || space(S.front())){
            return 0;
        }
        if(S.front() == '-'){
            goto READ_DD;
        }
        if(S.front() != ':'){
            return pos;
        }
        S.step();
        ++pos;
    }
    {
        auto dpos = read_digit(date.mm);
        if(dpos != 0){
            pos += dpos;
            return (pos == 0 ? -1 : pos) ;
        }
        if(S.empty() || space(S.front())){
            return 0;
        }
        if(S.front() == '-'){
            goto READ_DD;
        }
        if(S.front() != ':'){
            return pos;
        }
        S.step();
        ++pos;
    }
    {
        auto dpos = read_digit(date.ss);
        if(dpos != 0){
            pos += dpos;
            return (pos == 0 ? -1 : pos) ;
        }
        if(S.empty() || space(S.front())){
            return 0;
        }
        if(S.front() == '-'){
            goto READ_DD;
        } else {
            return 0;
        }
    }

    READ_DD:
    S.step();
    auto dpos = parse_int(S,date.days);
    if(dpos != 0){
        return  ( dpos > 0 ? pos + dpos : (pos > 0 ? pos : -1));
    }
    return 0;
}