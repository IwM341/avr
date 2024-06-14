#ifndef OPTIONAL_H
#define OPTIONAL_H

namespace asyncruino{

    template <typename T>
    struct optional{
        T value;
        bool valid;
        inline optional():valid(false){}
        inline optional(T value):value(value){}
        inline optional & operator = (T const& n_value){
            value = n_value;
            valid = true;
            return *this;
        }
        inline void reset(){valid = false;}
        inline operator bool()const{return valid;}

    };

};

#endif//OPTIONAL_H