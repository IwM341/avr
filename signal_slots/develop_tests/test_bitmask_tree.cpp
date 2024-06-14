#include <iostream>
#include <bitset>
#include "../include/rtu/bitmask.hpp"
#include "debug_defs.hpp"
#include <set>
using namespace std;


template<std::size_t N>
std::bitset<N>  reverse(std::bitset<N> b) {
	std::bitset<N> ret;
    for(std::size_t i = 0; i < N; ++i) {
        ret[i] = b[N-i-1];
    }
	return ret;
}



int main(void){
	typedef rtu::__int_detail::default_bit_funcs<uint8_t,size_t> int_traits;
	typedef rtu::bitmask_primitive_t<int_traits>  msk_t;
	typedef rtu::bitmask_tree_t<msk_t,8,int_traits> mask2_t;

	mask2_t m_mask(mask2_t::_1);
	
	auto print_mask = [&](){
		cout << "meta: " <<  reverse(std::bitset<8>(m_mask.meta_mask)) << endl;
		for(size_t i=0;i<8;++i){
			cout << reverse(std::bitset<8>(m_mask.masks[i])) << " ";
		}cout << endl;
	};
	print_mask();

	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();
	m_mask.occupy();

	print("occupy");

	print_mask();
	m_mask.release(9);
	print("release 9");
	print_mask();

	m_mask.occupy();
	print("occupy then");
	print_mask();

	set<size_t> occupied_indexes;
	
	mask2_t m_msk(mask2_t::_1);


	print("full count = ", mask2_t::full_count);
	auto erase_rand_element  = [&](){
		if(occupied_indexes.size()){
			size_t i = rand() % occupied_indexes.size();
			size_t sch = 0;
			for(auto idx : occupied_indexes){
				if(sch == i){
					m_msk.release(idx);
					occupied_indexes.erase(idx);
					print("erase element ", idx);
					break;
				}
				++sch;
			}
		}
	};
	auto print_msk = [&](){
		cout << "meta: " <<  reverse(std::bitset<8>(m_msk.meta_mask)) << endl;
		for(size_t i=0;i<8;++i){
			cout << reverse(std::bitset<8>(m_msk.masks[i])) << " ";
		}cout << endl;
	};

	print("start big test");
	print_msk();

	for(size_t i=0;i<1000;++i){
		if(occupied_indexes.size() == mask2_t::full_count)
		{
			erase_rand_element();
		} 
		else 
		{
			if(! (rand() % 4)){
				erase_rand_element();
			} else {
				size_t old_size = occupied_indexes.size();
				size_t occ = m_msk.occupy();
				print("occupy element ", occ);
				occupied_indexes.insert(occ);
				if(old_size == occupied_indexes.size()){
					print("TEST FAILED, allocation of same size");
					return 1;
				}
			}
		}
		print_msk();
	}
	return 0;
}