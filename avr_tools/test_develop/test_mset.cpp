#include <iostream>
#include <bitset>
#include "../avr_tools/include/micro_set.h"

using namespace std;
int main(void){
	aos::micro_set<int,7,true> X;

	cout << bitset<8>(decltype(X)::op_mask) <<endl;

	cout << (int) X.insert(10) <<endl;
	cout << (int) X.insert(13) <<endl;
	cout << (int) X.insert(32) <<endl;
	X.remove(13);
	cout << (int) X.insert(25) <<endl;


	cout << bitset<8>(X._mask) <<endl;
	cout << bitset<8>(X.size()) <<endl;
	return 0;
}