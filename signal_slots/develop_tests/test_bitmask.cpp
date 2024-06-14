#include <iostream>
#include <bitset>
#include "../include/rtu/bitmask.hpp"

using namespace std;
int main(void){
	rtu::bitmask_primitive_t<rtu::__int_detail::default_bit_funcs<uint8_t,size_t>> msk(rtu::bitmask_primitive_t<>::_1);
	cout << sizeof(size_t) <<endl;
	cout << "++++----" <<endl;
	cout << std::bitset<8>(msk) << endl;
	msk.set_bit_to_0(msk.get_1_pos());
	msk.set_bit_to_0(msk.get_1_pos());
	msk.set_bit_to_0(msk.get_1_pos());
	msk.set_bit_to_0(msk.get_1_pos());

	msk.set_bit_to_0(msk.get_1_pos());
	msk.set_bit_to_0(msk.get_1_pos());
	msk.set_bit_to_0(msk.get_1_pos());
	msk.set_bit_to_0(msk.get_1_pos());




	cout << "occupy bits 0--8" << endl;
	cout << "++++----" <<endl;
	cout << std::bitset<8>(msk) << endl;

	msk.set_bit_to_1(5);

	cout << "++++----" <<endl;
	cout << std::bitset<8>(msk) << endl;

	cout << msk.get_1_pos()  << endl;
	return 0;
}