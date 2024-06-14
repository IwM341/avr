#include <iostream>
#include "../include/rtu/bitmask.hpp"
#include "../include/rtu/memory_list.hpp"
#include "debug_defs.hpp"
struct no_guard{

};
using namespace std;
int main(void){
	typedef rtu::__int_detail::default_bit_funcs<uint8_t,size_t> int_traits;
	typedef rtu::bitmask_primitive_t<int_traits>  msk_t;
	typedef rtu::bitmask_tree_t<msk_t,8,int_traits> mask2_t;
	typedef rtu::bitmask_tree_t<mask2_t,8,int_traits> mask3_t;

	typedef rtu::mem_array_t<4,mask2_t> mem_arr_t;

	mem_arr_t arr;

	size_t idx =  arr.allocate();

	PVAR(idx);	

	PVAR(&arr);
	PVAR(&arr.get_node(idx));

	cout << arr <<endl;

	typedef rtu::mem_list_traits<mem_arr_t> list_traits;

	
	return 0;
}