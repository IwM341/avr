#ifndef SERIALIZATION_IMPL_HPP
#define SERIALIZATION_IMPL_HPP
#include <type_traits>
namespace rtu {
    namespace detail {
        template <typename T>
        struct alignas(alignof(T)) undestructable_value{
            
            inline static void * operator new (size_t size,void *p){return p;}

            static constexpr size_t size = sizeof(T); 
            char data[size];
            inline operator T & () {return *reinterpret_cast<T*>(data);}
            inline operator T const & ()const {return *reinterpret_cast<T*>(data);}
            
            template <typename...Args>
            inline void set_data(Args&&...args){
                new (data) T(static_cast<Args&&>(args)...);
            }
            template <typename...Args>
            inline undestructable_value(Args&&...args){
                set_data(static_cast<Args&&>(args)...);
            }
            inline void destroy(){
                ~T();
            }
        };
    };
};

#endif//SERIALIZATION_IMPL_HPP