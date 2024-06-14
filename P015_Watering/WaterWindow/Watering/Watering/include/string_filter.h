#pragma once

namespace StrFlt{
    
    template <typename Filter1,typename Filter2>
    struct filter_or;

    template <typename Filter1,typename Filter2>
    struct filter_and;

    template <typename Filter_t>
    struct filter_base{
        constexpr Filter_t & impl(){
            return static_cast<Filter_t &>(*this);
        }
        constexpr Filter_t const& impl()const{
            return static_cast<Filter_t const&>(*this);
        }

        template <typename Filter_1_t>
        constexpr filter_or<Filter_t,Filter_1_t> operator|
            (const filter_base<Filter_1_t> & _other) const
        {return {impl(),_other.impl()};}
        template <typename Filter_1_t>
        constexpr filter_and<Filter_t,Filter_1_t> operator&
            (const filter_base<Filter_1_t> & _other) const
        {return {impl(),_other.impl()};}
    };

    
    template <typename Filter1,typename Filter2>
    struct filter_or:public filter_base<filter_or<Filter1,Filter2>>{
        Filter1 _F1;
        Filter2 _F2;
        constexpr filter_or(Filter1  const & _F1, Filter2  _F2):
            _F1(_F1),_F2(_F2){}
        constexpr bool operator ()(char c)const{
            return _F1(c) || _F2(c);
        }
    };
    template <typename Filter1,typename Filter2>
    struct filter_and:public filter_base<filter_and<Filter1,Filter2>>{
        Filter1 _F1;
        Filter2 _F2;
        constexpr filter_and(Filter1 const & _F1, Filter2 const & _F2):
            _F1(_F1),_F2(_F2){}
        constexpr bool operator ()(char c)const{
            return _F1(c) && _F2(c);
        }
    };

    struct filter_letter_t:public filter_base<filter_letter_t>{
        constexpr bool operator ()(char c)const{
            return ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z'));
        }
    };
    struct filter_underscore_t:public filter_base<filter_underscore_t>{
        constexpr bool operator ()(char c)const{
            return c=='_';
        }
    };
    struct filter_space_t:public filter_base<filter_space_t>{
        constexpr bool operator ()(char c)const{
            return c=='\n' || c=='\t' || c=='\r' || c == ' ';
        }
    };
    struct filter_num_t:public filter_base<filter_num_t>
    {
        constexpr bool operator ()(char c)const{
            return c>='0' && c<='9';
        }
    };
    
    constexpr filter_letter_t letter{};
    constexpr filter_underscore_t underscore{};
    constexpr filter_space_t space{};
    constexpr filter_num_t num{};

    constexpr auto variable = letter|underscore|num;
    constexpr auto variable_begin = letter|underscore;
    
        
};