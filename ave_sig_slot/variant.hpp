#ifndef VARIANT_HPP
#define VARIANT_HPP
namespace __detail{
    struct __test__size{
        virtual ~__test__size(){}
    };

    template <size_t I,size_t...Other>
    struct static_max{
        constexpr static size_t value = (I >  static_max<Other...>::value ? I :   static_max<Other...>::value);
    };
    
    template <size_t I>
    struct static_max<I>{
        constexpr static size_t value = I;
    };

   
   template <typename T,typename...Args>
    struct contains;

    template <typename T,typename Arg0,typename...Args>
    struct contains<T,Arg0,Args...>{
        constexpr static bool value =contains<T,Arg0>::value || contains<T,Args...>::value;
    };
    template <typename T>
    struct contains<T,T>{
        constexpr static bool value =true;
    };
    template <typename T,typename U>
    struct contains<T,U>{
        constexpr static bool value =false;
    };

    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };
    
};
template <typename AbstractBase,typename...Childs>
struct static_ptr{
    inline AbstractBase * get(){
        return reinterpret_cast<AbstractBase*> (&_value);
    }
    inline const AbstractBase * get()const{
        return reinterpret_cast<const AbstractBase*> (&_value);
    }
    inline operator AbstractBase *(){return get();}
    inline operator AbstractBase *()const{return get();}

    template <typename ChildType,typename...Args>
    static inline typename __detail::enable_if<__detail::contains<AbstractBase,ChildType,Childs...>::value,static_ptr>::type 
        make_ptr(Args &&...args){
        static_ptr ptr;
        new  (reinterpret_cast<ChildType*>(&ptr)) ChildType(static_cast<Args &&>(args)...);
        return ptr;
    }
    ~static_ptr(){
        reinterpret_cast<AbstractBase*>(&_value)->~AbstractBase();
    }

    private:
    static_ptr(){}
    char  _value[__detail::static_max<sizeof(AbstractBase),sizeof(Childs)...>::value];

};


#endif