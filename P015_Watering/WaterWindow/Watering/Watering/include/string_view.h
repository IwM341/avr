#pragma once
#include <string.h>
namespace Std{

    struct string_view{
        private:
        const char * _data;
        size_t _size;
        public:
        constexpr string_view(const char * _data = NULL):
            _data(_data), _size(_data != NULL ? strlen(_data) : 0)
        {
        }
        constexpr string_view(const char * _data,size_t _size):
            _data(_data), _size(_size)
        {
        }

        inline size_t size(){
            return _size;
        }
        constexpr  char operator [](size_t i) const{
            return _data[i];
        }
        constexpr  char front() const{
            return *_data;
        }
        constexpr  char back() const{
            return _data[_size-1];
        }

        constexpr bool operator == (const char * _other)const{
            for(size_t i=0;i<_size;++i){
                if(_other[i] == 0){
                    return _data[i] == 0;
                }else if(_other[i] != _data[i]){
                    return false;
                }
                return true;
            }
        }
        constexpr bool operator !=(const char * _other)const{
            return !(this->operator==(_other));
        }
        friend constexpr bool operator ==(const char * _other,string_view const &_this){
            return _this ==_other;
        }
        friend constexpr bool operator !=(const char * _other,string_view const &_this){
            return _this !=_other;
        }
        constexpr bool  operator ==(string_view const &_other){
            if(_size != _other._size){
                return false;
            }
            for(size_t i=0;i<_size;++i){
                if(_data[i] != _other[i]){
                    return false;
                }
            }
            return true;
        }
        constexpr bool  operator !=(string_view const &_other){
            return !((*this) == _other);
        }

        constexpr string_view substr(size_t start,size_t _n_size){
            return string_view(_data + start,_n_size);
        }
        constexpr string_view substr(size_t start){
            return string_view(_data + start,_size-start);
        }

        const char * begin(){
            return _data;
        }
        const char * end(){
            return _data+_size;
        }

        void step(){
            _size--;
            _data++;
        }
        bool empty(){
            return _size == 0;
        }
    };

    string_view operator""sv(const char * _str,size_t _len){
        return string_view(_str,_len);
    }
};