#ifndef BITMASK_HPP
#define BITMASK_HPP

#include "int_traits.hpp"

namespace rtu {

    namespace __int_detail {    
        template <typename _int_type,typename _index_type = unsigned char>
        struct default_bit_funcs{
            typedef _int_type int_type;
            typedef _index_type index_type;
            inline static index_type popcount(int_type x){
                return __builtin_popcount (x);
            }
            /*position of first non zero bit*/
            inline static index_type ctz(int_type x){
                return __builtin_ctz(x);
            }
        };
        template <typename int_type,size_t one_nums>
        struct ones{
            static constexpr  int_type value = (1 << (one_nums-1)) | ones<int_type,one_nums-1>::value;
        };

        template <typename int_type>
        struct ones<int_type,0>{
            static constexpr  int_type value = 0;
        };
    };
    /*
    0 - bit occupied
    1 - bit free 
    */

    /// @brief 
    /// @tparam int_type_traits struct, which hase type field (int type) and functions popcount (bitnum) and ctz (first nonzero bit)
    template <typename int_type_traits = __int_detail::default_bit_funcs<ARCH_SIZE_TYPE,ARCH_SIZE_TYPE> >
    struct bitmask_primitive_t {
        typedef typename int_type_traits::int_type int_type;
        typedef typename int_type_traits::index_type index_type;
        int_type mask;
        
        static constexpr size_t full_count = bit_size<int_type>::value;

        constexpr inline bitmask_primitive_t() {}
        constexpr inline bitmask_primitive_t (int_type mask): mask(mask) {}
        constexpr static bitmask_primitive_t _0 = 0;
        constexpr static bitmask_primitive_t _1 = ~_0;
        inline constexpr operator int_type & () {
            return mask;
        }
        inline constexpr operator int_type const& () const{
            return mask;
        }

        inline constexpr index_type count0 ()const{
            return int_type_traits::popcount(~mask);
        };
        inline constexpr index_type count1 ()const{
            return int_type_traits::popcount(mask);
        };

        inline constexpr index_type get_1_pos() const{
            return int_type_traits::ctz(mask);
        };

        inline constexpr index_type occupy(){
            index_type pos = get_1_pos();
            set_bit_to_0(pos);
            return pos;
        };

        inline constexpr void set_bit_to_1(index_type position){
            mask |= 1<<position;
        };
        inline constexpr void set_bit_to_0(index_type position){
            mask &= ~(1<<position);
        };

        inline constexpr void release(index_type position){
            mask |= 1<<position;
        };

        inline bool full() const{
            return mask == 0;
        }
    };
    template <typename bitmask_type,size_t bitmask_num, typename int_type_traits>
    struct bitmask_tree_t {
        bitmask_type masks[bitmask_num];

        typedef bitmask_primitive_t<int_type_traits> meta_mask_t;
        meta_mask_t meta_mask;


        static constexpr size_t full_count = bitmask_num*bitmask_type::full_count;
        typedef typename min_type_for_size<full_count>::type index_type; 


        static constexpr inline auto get_meta_head(index_type x) {
            return x >> __int_detail::log2u<bitmask_type::full_count>::value;
        }
        static constexpr inline auto save_meta_head(index_type x) {
            return x << __int_detail::log2u<bitmask_type::full_count>::value;
        }
        static constexpr inline auto get_tail(index_type x) {
            return x & __int_detail::ones<index_type, __int_detail::log2u<bitmask_type::full_count>::value>::value;
        }

        struct bitmask_zero_initializer{};
        struct bitmask_ones_initializer{};

        constexpr inline bitmask_tree_t() {}
        constexpr static bitmask_zero_initializer _0{};
        constexpr static bitmask_ones_initializer _1{};
        constexpr inline bitmask_tree_t(bitmask_zero_initializer): 
        meta_mask(meta_mask_t::_0)
        {
            for( ARCH_SIZE_TYPE i =0;i<bitmask_num;++i){
                masks[i] = bitmask_type(bitmask_type::_0);
            }

        }
        constexpr inline bitmask_tree_t(bitmask_ones_initializer): 
        meta_mask(__int_detail::ones<typename int_type_traits::int_type,bitmask_num>::value)
        {
            for( ARCH_SIZE_TYPE i =0;i<bitmask_num;++i){
                masks[i] = bitmask_type::_1;
            }
        }

        inline constexpr index_type count0 () const{
            index_type sch = 0;
            for(ARCH_SIZE_TYPE i = 0;i < bitmask_num;++i){
                if( ~meta_mask & (1 << bitmask_num) ){
                    sch += bitmask_type::full_count;
                }else{
                    sch +=  masks[i].count0();
                }
            }
            return sch;
        };
        inline constexpr index_type count1 () const{
            index_type sch = 0;
            for(ARCH_SIZE_TYPE i = 0;i < bitmask_num;++i){
                if( ~meta_mask & (1 << bitmask_num) ){
                    sch += bitmask_type::full_count;
                }else{
                    sch +=  masks[i].count0();
                }
            }
            return sch;
        };

        inline constexpr index_type get_1_pos() const {
            index_type i = meta_mask.get_1_pos();
            return save_meta_head(i) | (masks[i].get_1_pos());
        };


        inline constexpr index_type occupy() {
            index_type meta_pos = meta_mask.get_1_pos();
            index_type tail_pos = masks[meta_pos].occupy();
            if(masks[meta_pos].full()){
                meta_mask.set_bit_to_0(meta_pos);
            }
            return  save_meta_head(meta_pos) | tail_pos;
        };

        inline constexpr void set_bit_to_1(index_type position){
            auto meta_pos = get_meta_head(position);
            meta_mask.set_bit_to_1 (meta_pos);
            masks[meta_pos].set_bit_to_1(get_tail(position));
        };
        inline constexpr void set_bit_to_0(index_type position){
            auto meta_pos = get_meta_head(position);
            masks[meta_pos].set_bit_to_0(get_tail(position));
            if(masks[meta_pos].full()){
                meta_mask.set_bit_to_0(meta_pos);
            }
        };

        inline constexpr void release(index_type position){
            auto meta_pos = get_meta_head(position);
            meta_mask.set_bit_to_1 (meta_pos);
            masks[meta_pos].release(get_tail(position));
        };

        inline bool full() const{
            return meta_mask == 0;
        }
    };

    
};

#endif//BITMASK_HPP