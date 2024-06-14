#pragma once
#include <stdlib.h>
#include <concepts>
#include <math.h>
namespace asyncruino{
    

    
    namespace time_prefix{
        constexpr static int ps = -12;
        constexpr static int ns = -9;
        constexpr static int mus = -6;
        constexpr static int ms = -3;
        constexpr static int s = 0;
        constexpr static int Ks = 3;
        constexpr static int Ms = 6;
    };
    template <int m_prefix>
    struct time_prefix_t{
        constexpr static int value = m_prefix;
    };

    namespace time_literals{
        #define _DEC_LIT_T(prefix) \
        constexpr static time_prefix_t<time_prefix::prefix> prefix = {};

        _DEC_LIT_T(ps)
        _DEC_LIT_T(ns)
        _DEC_LIT_T(mus)
        _DEC_LIT_T(ms)
        _DEC_LIT_T(s)
        _DEC_LIT_T(Ks)
        _DEC_LIT_T(Ms)
        #undef _DEC_LIT_T
        
    };
    


    template <typename counter_t,typename dividor_t,int _base>
    struct timer_dim_counter{
        typedef counter_t counter_type;
        typedef dividor_t dividor_type;
        constexpr static int base = _base;
        
        counter_t value;
        dividor_t prefix_sec_per_tick;
        dividor_t tick_per_prefix_sec;

        
        template <int _m_prefix = _base>
        timer_dim_counter(
            dividor_t _prefix_sec_per_tick,
            time_prefix_t<_m_prefix> m_prefix_t= {}
            ):value(0){
                set_speed(_prefix_sec_per_tick,m_prefix_t);
            }
        
        template <int _m_prefix = _base>
        inline void set_speed(dividor_t prefix_sec_per_tick,
            time_prefix_t<_m_prefix> = {})
        {
            constexpr int8_t base_diff = (int8_t)_m_prefix - (int8_t)base;
            constexpr dividor_t pow_10 = pow(10.0,base_diff);
            prefix_sec_per_tick = prefix_sec_per_tick*pow_10;
            tick_per_prefix_sec= 1/prefix_sec_per_tick;   
        }
        inline counter_t count() const{
            return value;
        }

        template <int other_base = base>
        inline auto current() const{
            auto numerator = value*prefix_sec_per_tick;
            if constexpr (other_base == base){
                return numerator;
            }
            constexpr int8_t base_diff = (int8_t)base - (int8_t)other_base;
            constexpr dividor_t pow_10 = pow(10.0,base_diff); 
            return numerator*pow_10;
        }
        template <int8_t other_base>
        inline auto current(time_prefix_t<other_base>) const{
            return current<other_base>();
        }

        template <int8_t other_base = base,typename T>
        inline counter_t to_counter_t(T _value) const{
            if constexpr (other_base == base){
                return _value*tick_per_prefix_sec;
            }
            constexpr int8_t base_diff = (int8_t)other_base - (int8_t)base;
            constexpr dividor_t pow_10 = pow(10.0,base_diff);
            return _value*tick_per_prefix_sec*pow_10;
        }
        template <typename T,int other_base>
        inline  counter_t to_counter_t(T _value,time_prefix_t<other_base>) const{
            return to_counter_t<other_base>(_value);
        }
    };
    template <typename timer_dim_counter_t>
    concept CounterImpl = requires (timer_dim_counter_t t){
        {timer_dim_counter{t}}->std::same_as<timer_dim_counter_t>;
    };

};