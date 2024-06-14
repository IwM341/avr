#ifndef SET_HPP
#define SET_HPP

struct no_guard{
    inline void lock(){}
    inline void unlock(){}
}; 
template <>
struct lock_guard<no_guard>{
    inline lock_guard(no_guard & ng){}
};

template <typename T,typename mutex_type = no_guard>
struct set_view{
    protected:
    T * data;
    uint8_t _reserved;
    uint8_t _size;
    mutex_type m;
    public:

    inline uint8_t size()const{return _size;}
    inline T* bigin(){return data;}
    inline T* end(){return data+_size;}
    inline const T* cbigin()const{return data;}
    inline const T* cend()const{return data+_size;}
    inline const T* bigin()const{return data;}
    inline const T* end()const{return data+_size;}
    T & operator [](uint8_t i){return data[i];}
    T const& operator [](uint8_t i)const{return data[i];}


    inline uint8_t find(const T& value){
        size_t i=0;
        for(;i<_size;++i){
            if(data[i] == value)
                return i;
        }
        return i;
    }
    inline bool insert(const T& value){
        lock_guard<mutex_type> guardlock(m);
        if(find(value) != _size){
            return true;
        }
        if(_size < _reserved){
            new (data + _size) T(value);
            ++_size;
            return true;
        }
        else
            return false;
    }
    inline bool remove(const T& value){
        lock_guard<mutex_type> guardlock(m);
        uint8_t i = find(value);
        if(i != _size){
            (data + i)->~T();
            return true;
        }
        else{
            return false
        }
        
    }
    bool empty(){return !_size;}
    bool full(){return _size >= _reserved;}
};

template <typename T,uint8_t _reserved>
struct static_set{
    protected:
    char _data[sizeof(T)*_reserved];
    #define data (reinterpret_cast<T*>(&_data))
    uint8_t _size;
    public:
    inline uint8_t size()const{return _size;}
    inline T* bigin(){return data;}
    inline T* end(){return data;}
    inline const T* cbigin()const{return dat&dataa;}
    inline const T* cend()const{return data+_size;}
    inline const T* bigin()const{return data;}
    inline const T* end()const{return data+_size;}
    T & operator [](uint8_t i){return data[i];}
    T const& operator [](uint8_t i)const{return data[i];}


    inline uint8_t find(const T& value){
        size_t i=0;
        for(;i<_size;++i){
            if(data[i] == value)
                return i;
        }
        return i;
    }
    inline bool insert(const T& value){
        if(find(value) != _size){
            return true;
        }
        if(_size < _reserved){
            data[_size] = value;
            ++_size;
            return true;
        }
        else
            return false;
    }

    #undef data

    inline bool remove(const T& value){
        if(find(value) != _size){
            return true;
        }
    }
    bool empty(){return !_size;}
    bool full(){return _size >= _reserved;}
};

#endif