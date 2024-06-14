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

    

    template <size_t node_size,typename bitmask_t,typename guard_t = no_guard_t>
    struct mem_array_t {
        constexpr static size_t size = bitmask_t::full_count;
        typedef mem_node_t<node_size> node_t;
        typedef typename node_t::index_type index_t;
        node_t data[size];
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

    template <typename mem_array_type>
    struct mem_list_traits {
        typedef typename mem_array_type::node_t node_t;
        typedef typename mem_array_type::index_t index_t;

        inline constexpr static index_t create(mem_array_type & mem_array,index_t next = 0){
            index_t ret = mem_array.sallocate();
            mem_array.get_node(ret).next = next;
            return ret;
        }

        inline static index_t remove_node(mem_array_type & mem_array,
        index_t & start_pointer){
            start_pointer = mem_array.get_node(start_pointer).next;
        }

        /// @brief creates memory to copy data to it
        /// @param x data to copy
        /// @param length data length
        /// @param node_shift start position to wright into node
        /// @param index position of list, 
        /// would be changed to created position if index = 0
        /// @param mem_array mem storage instance
        template <typename shift_type>
        inline static constexpr void create_list_with_copy(
                const char * x,shift_type length,shift_type & node_shift,index_t & index,
                mem_array_type & mem_array) 
        {
            if(!index){
                index = mem_array.sallocate();
            }
            auto & node = mem_array.get_node( index);
            if( node_shift + length <= node_t::data_size){
                std::memcpy(node.data + node_shift,x,length);
                node_shift = node_shift + length;
            } else {
                shift_type cpy_size = node_t::data_size - node_shift;
                std::memcpy(node.data + node_shift,x,cpy_size);
                index = node.next();
                node_shift = 0;
                create_list_with_copy(x + node_t::data_size - node_shift,
                                    length - cpy_size,node_shift,
                                    index);
            }
        }
        template <typename shift_type>
        inline static constexpr void copy_data_from_list(char * x,shift_type length,shift_type & node_shift,index_t & index,
                                            mem_array_type & mem_array) {
            if(!length)
                return;
            auto & node = mem_array.get_node( index);
            if( node_shift + length <= node_t::data_size){
                node_shift = node_shift + length;
                std::memcpy(x,node.data + node_shift,length);
            } else {
                shift_type cpy_size = node_t::data_size - node_shift;
                std::memcpy(x,node.data + node_shift,cpy_size);
                index = node.next();
                node_shift = 0;
                copy_data_from_list(x - cpy_size,length - cpy_size,node_shift,index);
            }
        }

        /// @brief moves data from list WITHOUT deleting last node 
        /// @param x output data
        /// @param length length to copy
        /// @param node_shift start position to read fromnode
        /// @param index position of list, 
        /// would be changed to last position
        /// @param mem_array mem array
        template <typename shift_type>
        inline static constexpr void move_data_from_list_soft(char * x,shift_type length,shift_type & node_shift,index_t & index,
                                            mem_array_type & mem_array) {
            if(!length)
                return;
            auto & node = mem_array.get_node( index);
            if( node_shift + length <= node_t::data_size){
                node_shift = node_shift + length;
                std::memcpy(x,node.data + node_shift,length);
                if(node_shift == node_t::data_size){
                    node_shift = 0;
                    index = node.next();
                }
            } else {
                shift_type cpy_size = node_t::data_size - node_shift;
                std::memcpy(x,node.data + node_shift,cpy_size);
                auto prev_index = index;
                index = node.next();
                mem_array.sdeallocate(prev_index);
                node_shift = 0;
                move_data_from_list_soft(x - cpy_size,length - cpy_size,node_shift,index);
            }
        }

        /// @brief moves data from list DELETING LAST NODE 
        /// @param x output data
        /// @param length length to copy
        /// @param node_shift start position to read fro mnode
        /// @param index position of list, 
        /// would be changed to last position
        /// @param mem_array mem array
        template <typename shift_type>
        inline static constexpr void move_data_from_list_full(char * x,shift_type length,shift_type & node_shift,index_t & index,
                                            mem_array_type & mem_array) {
            if(!length)
                return;
            auto & node = mem_array.get_node( index);
            if( node_shift + length <= node_t::data_size){
                node_shift = node_shift + length;
                std::memcpy(x,node.data + node_shift,length); 
                auto prev_index = index;
                index = node.next;
                mem_array.sdeallocate(prev_index);
            } else {
                shift_type cpy_size = node_t::data_size - node_shift;
                std::memcpy(x,node.data + node_shift,cpy_size);
                auto prev_index = index;
                index = node.next();
                mem_array.sdeallocate(prev_index);
                node_shift = 0;
                move_data_from_list_full(x - cpy_size,length - cpy_size,node_shift,index);
            }
        }

        template <typename T,typename shift_type>
        inline static constexpr void fill_value(T const & x,shift_type & node_shift,index_t & index,
                                            mem_array_type & mem_array) {
            create_list_with_copy((const char * )(&x),sizeof(T),node_shift,index,mem_array);
        }
        
        template <typename T,typename shift_type>
        inline static constexpr T load_value_soft(shift_type & node_shift,index_t & index,
                                            mem_array_type & mem_array) {  
            T x;
            move_data_from_list_soft((char * )&x,sizeof(T),node_shift,index,mem_array);
            return x;
        }
        template <typename T,typename shift_type>
        inline static constexpr T load_value_full(shift_type & node_shift,index_t & index,
                                            mem_array_type & mem_array) {  
            T x;
            move_data_from_list_full((char * )&x,sizeof(T),node_shift,index,mem_array);
            return x;
        }
    }; 
};

#endif//MEMORY_LIST_HPP