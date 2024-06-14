#ifndef MEMORY_LIST_HPP
#define MEMORY_LIST_HPP

#include "int_traits.hpp"
#include <cstring>
#include "default_guard.hpp"
namespace rtu{

    template <size_t _size>
    struct alignas(alignof(max_align_t)) mem_node_t  {
        char data[_size];
        constexpr static size_t data_size = _size;
    };

    

    template <size_t node_size,size_t _size,typename bitmask_t,typename guard_t = no_guard_t>
    struct mem_array_t {
        typedef mem_node_t<node_size> node_t;
        constexpr static size_t size = _size;
        constexpr static size_t leaf_size = sizeof(node_t);
        typedef typename min_type_for_size<_size>::type index_t;

        node_t data[_size];
        bitmask_t mask;
        guard_t __guard;

        mem_array_t() : mask(bitmask_t::_1) {
            mask.set_bit_to_0(0);

            /*begin {remove it section}*/
            for(size_t j=0;j<size;++j){
                for(size_t i=0;i<node_t::data_size;++i){
                    get_node(j+1).data[i] = '*';
                }
            }
            /*end {remove it section}*/
        }

        /*begin {remove it section}*/
        friend std::ostream & operator << (std::ostream & of,mem_array_t const & mem){
            for(size_t j=0;j<size;++j){
                of << "{" << j +1<< "}[" << mem.get_node(j+1).data << "](" << (size_t)mem.get_node(j+1).next << ")";
                if(j == size-1){
                    of << std::endl;
                }
                else{
                    of << "-->";
                }
            }
            return of;
        }
        /*end {remove it section}*/

        inline constexpr node_t & get_node(index_t lf_index){
            return *(data + lf_index - 1);
        }
        inline constexpr node_t  const & get_node(index_t lf_index) const{
            return *(data + lf_index - 1);
        }
        inline constexpr index_t get_index(node_t * _node) const{
            return _node-&data;
        }
        inline constexpr index_t allocate(){
            index_t position = mask.occupy();
            /*begin {remove it section}*/
            for(size_t i=0;i<node_t::data_size;++i){
                get_node(position).data[i] = '|';
            }
            /*end {remove it section}*/
            return position;
        }
        inline constexpr void deallocate(index_t position){
            /*begin {remove it section}*/
            for(size_t i=0;i<node_t::data_size;++i){
                data[position].data[i] = '*';
            }
            /*end {remove it section}*/
            mask.set_bit_to_1(position);
        }
        inline void occupy(){
            __guard.lock();
        }
        inline void release(){
            __guard.unlock();
        }
        inline constexpr index_t sallocate(){
            __guard.lock();
            index_t position = mask.get_1_pos();
            data[position].next_index = 0;
            mask.set_bit_to_0(position);
            __guard.unlock();
        } 
        inline constexpr void sdeallocate(index_t position){
             __guard.lock();
            mask.set_bit_to_1(position);
             __guard.unlock();
        }
    };
};

#endif//MEMORY_LIST_HPP