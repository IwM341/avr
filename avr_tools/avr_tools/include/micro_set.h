#ifndef MICRO_SET_H
#define MICRO_SET_H

#include "size_types.h"


namespace aos{
namespace __detail__{
    template <typename mask_type,uint8_t _reserved>
    struct op_mask{
        constexpr static mask_type value = (1<<_reserved)-1;
    };
    template <uint8_t _value>
    struct uint8_t_constant{};
    template <typename mask_type,uint8_t log2_mask_semi_period,typename bitnum_constant>
    struct _periodic_mask;

    template <typename mask_type,uint8_t log2_mask_semi_period,uint8_t bitnum>
    struct _periodic_mask<mask_type,log2_mask_semi_period,uint8_t_constant<bitnum>>{
        constexpr static mask_type value = (bitnum%(1<<(log2_mask_semi_period+1)) < (1<<log2_mask_semi_period)) |
                        ((_periodic_mask<mask_type,log2_mask_semi_period,uint8_t_constant<bitnum+1>>::value)<<1);
    };

    template <typename mask_type,uint8_t log2_mask_semi_period>
    struct _periodic_mask<mask_type,log2_mask_semi_period,uint8_t_constant<sizeof(mask_type)*8-1>>{
        constexpr static mask_type value = ((sizeof(mask_type)*8-1)%(1<<(log2_mask_semi_period+1)) < (1<<log2_mask_semi_period));
    };

    template <typename mask_type,uint8_t log2_mask_semi_period>
    struct periodic_mask{
        constexpr static mask_type value = _periodic_mask<uint32_t,log2_mask_semi_period,uint8_t_constant<0>>::value;
    };

    

    template <uint8_t log2_reserved,typename mask_type,uint8_t log2_mask_semi_period = 0>
    struct popcnt_s{
        constexpr static  __attribute__((always_inline)) uint8_t res(mask_type mask){
            //std::cout << "popcnt_s"  <<std::endl;
            //std::cout << std::bitset<8>(mask) <<std::endl;
            //std::cout << (int)log2_mask_semi_period <<std::endl;
            //std::cout << (int)log2_reserved <<std::endl;

            mask = (mask & periodic_mask<mask_type,log2_mask_semi_period>::value) + 
            ( (mask >> (1<<log2_mask_semi_period)) & periodic_mask<mask_type,log2_mask_semi_period>::value);
            return popcnt_s<log2_reserved,mask_type,log2_mask_semi_period+1>::res(mask);
        }
    };

    template <uint8_t log2_reserved,typename mask_type>
    struct popcnt_s<log2_reserved,mask_type,log2_reserved>{
        constexpr static  __attribute__((always_inline))  uint8_t res(mask_type mask){
            //std::cout << "popcnt_final"  <<std::endl;
            //std::cout << std::bitset<8>(mask) <<std::endl;
            //std::cout << (int)log2_reserved <<std::endl;
            return mask;
        }
    };

    template <uint32_t _arg>
    struct log2up{
        constexpr static uint8_t value = 1 +log2up<(_arg+1)/2>::value;
    };
    template <>
    struct log2up<1>{
        constexpr static uint8_t value = 0;
    };
    

    template <typename size_type,uint8_t op_mask_len>
    struct first1{
        constexpr static  __INLINE__ uint8_t res(size_type mask){      
            return (op_mask<size_type,op_mask_len>::value & mask 
                ? first1<size_type,op_mask_len/2>::res(mask) : 
                op_mask_len+first1<size_type,op_mask_len/2>::res(mask >> op_mask_len));
        }
    };

    template <typename size_type>
    struct first1<size_type,0>{
        constexpr static  __INLINE__ uint8_t res(size_type mask){
            return 0;
        }
    };
    
};

#define _data (reinterpret_cast<T*>(__data__))
template <typename T,uint8_t _reserved,bool cache_size = false>
struct micro_set{
    char __data__[_reserved*sizeof(T)];
    typedef typename conditional<_reserved <= 8,uint8_t,
            typename conditional<_reserved <= 16,uint16_t,
            typename conditional<_reserved <= 32,uint32_t,
            typename conditional<_reserved <= 64,uint64_t,void>::type>::type>::type>::type mask_type;
    
    mask_type _mask;

    constexpr static mask_type op_mask = ((1<<_reserved) - 1);
    constexpr static mask_type not_op_mask = ~op_mask;

    __INLINE__ T * data(){return _data;}
    __INLINE__ micro_set():_mask(0){}
    __INLINE__ bool is_empty()const{return _mask;}
    __INLINE__ bool contain(uint8_t mask)const{return _mask&mask;}
    __INLINE__ bool is_not_empty()const{return _mask & op_mask;}
    __INLINE__ bool is_full()const{
        //auto x = not_op_mask;
        //auto y =  _mask | not_op_mask;
        return ~(_mask | not_op_mask);
    }

    __INLINE__ uint8_t size()const{
        return __detail__::popcnt_s<__detail__::log2up<_reserved>::value-1,mask_type>::res(_mask);
    }
    
    template <typename...Args>
    inline uint8_t insert(Args&&...args){
        if(!is_full()){
            return false;
        }else{
            uint8_t pos = __detail__::first1<mask_type,
                        ((1<<__detail__::log2up<_reserved>::value)/2)>::res(~_mask);
            new (_data + pos) T(static_cast<Args&&>(args)...);
            _mask |= 1<<pos;
            return pos;
        } 
    }
    inline void remove(T const&value){
         mask_type _sch_mask_end = 1<<_reserved;
         mask_type _sch_mask = 1;
         T * ptr = _data;
        while(_sch_mask != _sch_mask_end){
            if((_sch_mask & _mask) && *ptr == value){
                ptr->~T();
                _mask &= ~_sch_mask;
            }
            ptr++;
            _sch_mask = _sch_mask <<1;
        }
    }
    inline void remove_it(uint8_t _pos){
        (_data+_pos)->~T();
        _mask &= ~(1<<_pos);
    }
    template <typename ConditionType>
    inline void remove_if(ConditionType && cond){
         mask_type _sch_mask_end = 1<<_reserved;
         mask_type _sch_mask = 1;
         T * ptr = _data;
        while(_sch_mask != _sch_mask_end){
            if((_sch_mask & _mask) && cond(*ptr)){
                ptr->~T();
                _mask &= ~_sch_mask;
            }
            ptr++;
            _sch_mask = _sch_mask <<1;
        }
    }

    inline uint8_t find(T const&value){
         mask_type _sch_mask_end = 1<<_reserved;
        mask_type _sch_mask = 1;
        uint8_t it = 0;
        T * ptr = _data;
        while(_sch_mask != _sch_mask_end){
            if((_sch_mask & _mask) && *ptr == value){
                ptr->~T();
                _mask &= ~_sch_mask;
            }
            ptr++;
            _sch_mask = _sch_mask <<1;
            ++it;
        }
        return it;
    }

    template <typename ConditionType>
    uint8_t find_if(ConditionType && cond){
         mask_type _sch_mask_end = 1<<_reserved;
         mask_type _sch_mask = 1;
        uint8_t it = 0;
         T * ptr = _data;
        while(_sch_mask != _sch_mask_end){
            if((_sch_mask & _mask) && cond(*ptr)){
                ptr->~T();
                _mask &= ~_sch_mask;
            }
            ptr++;
            _sch_mask = _sch_mask <<1;
            ++it;
        }
        return it;
    }
};
/*
template <typename T,uint8_t _reserved>
struct micro_set<T,_reserved,true>{
    char __data__[_reserved*sizeof(T)];
    typedef typename conditional<_reserved <= 8,uint8_t,
            typename conditional<_reserved <= 16,uint16_t,
            typename conditional<_reserved <= 32,uint32_t,
            typename conditional<_reserved <= 64,uint64_t,void>::type>::type>::type>::type mask_type;
    
    mask_type _mask;
    uint8_t _size;

    constexpr static mask_type op_mask = ((1<<_reserved) - 1);
    constexpr static mask_type not_op_mask = ~op_mask;

    __INLINE__ micro_set():_mask(0),_size(0){}
    __INLINE__ bool is_empty()const{return _mask;}
    __INLINE__ bool is_not_empty()const{return _mask & op_mask;}
    __INLINE__ bool is_full()const{return ~(_mask & op_mask);}

    __INLINE__ uint8_t size()const{
        return _size;
    }
    
    template <typename...Args>
    inline uint8_t insert(Args&&...args){
        uint8_t sch = _reserved;
        if(!is_full()){
            return _reserved;
        }else{
            uint8_t pos = __detail__::first1<mask_type,
                        (1<<__detail__::log2up<_reserved>::value)/2
                        >::res(~_mask);
            new (_data + pos) T(static_cast<Args&&>(args)...);
            _mask |= 1 << pos;
            _size++;
            return pos;
        } 
    }
    inline void remove(T const&value){
         mask_type _sch_mask_end = 1<<_reserved;
         mask_type _sch_mask = 1;
         T * ptr = _data;
        while(_sch_mask != _sch_mask_end){
            if((_sch_mask & _mask) && *ptr == value){
                ptr->~T();
                _mask &= ~_sch_mask;
            }
            ptr++;
            _sch_mask = _sch_mask <<1;
        }
    }
    template <typename ConditionType>
    inline void remove_if(ConditionType && cond){
         mask_type _sch_mask_end = 1<<_reserved;
         mask_type _sch_mask = 1;
         T * ptr = _data;
        while(_sch_mask != _sch_mask_end){
            if((_sch_mask & _mask) && cond(*ptr)){
                ptr->~T();
                _mask &= ~_sch_mask;
            }
            ptr++;
            _sch_mask = _sch_mask <<1;
        }
    }
};
*/
template <typename T,bool cache_size>
struct micro_set<T,0,cache_size>{
    constexpr static uint8_t op_mask = 0;
    constexpr static uint8_t not_op_mask = ~op_mask;

    constexpr  bool is_empty()const{return true;}
    constexpr  bool is_not_empty()const{return false;}
    constexpr  bool is_full()const{return true;}
    __INLINE__ bool contain(uint8_t mask)const{return false;}
    
    typedef uint8_t mask_type;

    __INLINE__ T * data(){return nullptr;}
    constexpr uint8_t size()const{
        return 0;
    }
    
    inline bool insert(const T&){return false;}
    template <typename...Args>
    inline bool insert(Args&&...){return false;}
    inline void remove(T * ){}
    inline void remove_compare(const T&){}
    inline void remove_it(uint8_t _pos){}

    template <typename ConditionType>
    inline void remove_if(ConditionType &&){}
};

#undef _data

};
#endif//MICRO_SET_H