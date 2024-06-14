#ifndef INT_TRAITS_HPP
#define INT_TRAITS_HPP


#ifndef ARCH_SIZE_TYPE
#ifdef WIN32
#define ARCH_SIZE_TYPE size_t
#else
#define ARCH_SIZE_TYPE uint8_t
#endif
#endif
//#define M_SIZE_T uint16_t
//#define M_SIZE_T uint32_t
//#define M_SIZE_T uint64_t

#include <type_traits>
#include <climits>
#include <cstddef> 

#define min(a,b) ( (a) > (b) ? (b) : (a))
#define max(a,b) ( (a) < (b) ? (b) : (a))
namespace rtu {

    namespace int_func{
        template <size_t N>
        struct pow2 {
            static constexpr size_t value = ((size_t)1) <<N;
        };

        template <size_t N>
        struct log2d {
            static constexpr size_t value = 1 + log2d< (N >> 1)>::value;
        };
        template <>
        struct log2d<1> {
            static constexpr size_t value = 0;
        };

        template <size_t N>
        struct log2u {
            static constexpr size_t value = (N == pow2<log2d<N>::value>::value ? log2d<N>::value : 1 + log2d<N>::value);
        };
        template <>
        struct log2u<1> {
            static constexpr size_t value = 0;
        };
    };

    template <size_t size>
    struct min_type_for_size{
        typedef
            typename std::conditional< (size < __int_detail::pow2<8>::value),uint8_t,
                typename std::conditional< (size < __int_detail::pow2<16>::value),uint16_t,
                    typename std::conditional< (size < __int_detail::pow2<32>::value),uint32_t,
                        uint64_t
                    >::type
                >::type
            >::type
        type;
    };

    template <typename int_type>
    struct bit_size{
        static constexpr size_t value = sizeof(int_type)*CHAR_BIT;
    };

    template <size_t max_alignment,typename int_type = size_t>
    struct ex_size_t{
        static constexpr size_t alignment_bits = 
        int_func::log2u<max_alignment>::value;
        static constexpr size_t data_bits = 
        int_func::log2u<max_alignment>::value;
        
        static constexpr int_type size_mask = ones<int_typebit_size,
            bit_size<int_type>::value - alignment_bits>;
        
        static constexpr int_type alignment_mask = ~size_mask;

        int_type ex_data;
        inline operator int_type () const{
            return ex_data & size_mask;
        }
        inline constexpr ex_size_t(int_type value = 0,int_type log2align = 0):
        ex_data( (log2align << data_bits) | (value & size_mask)) {}

        inline int_type get_log2align(){
            return ex_data >> data_bits;
        }
        inline int_type get_align(){
            return 1 << (ex_data >> data_bits);
        }


    };

    


};

#endif//INT_TRAITS_HPP