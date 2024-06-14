#include <iostream>
#include "../avr_tools/include/delegator.h"
#include "../avr_tools/include/size_types.h"
//#include "../avr_tools/include/signals.h"
using namespace std;
template <typename T>
void pt(){
	cout << __PRETTY_FUNCTION__<<endl;
}

void my_function(){
	cout << __PRETTY_FUNCTION__<<endl;
}

void my_function_1(int x){
	cout << __PRETTY_FUNCTION__<<", x = " <<  x<<endl;
}

struct my_class{
	int x;
	my_class(int x = 42):x(x){}

	void f1(){
		cout << __PRETTY_FUNCTION__ <<", x = " <<  x <<endl;
	}
	void f2(int y){
		cout << __PRETTY_FUNCTION__ <<", x = " <<  x<<", y = " <<  y  <<endl;
	}
};

int main(void){
	my_class C;
	my_function();
	my_function_1(10);
	C.f1();
	C.f2(10);

	cout << "---------------------"<<endl;
	aos::ClassDelegator<> c1(&C,&my_class::f1);
	aos::ClassDelegator<int> c2(&C,&my_class::f2);
	aos::FunctionDelegator<> f1(my_function);
	aos::FunctionDelegator<int> f2(my_function_1);

	f1.call();
	f2.call(10);

	c1.call();
	c2.call(10);
	
	cout << "---------------------"<<endl;
	aos::ClassOrFunctionDelegator<> ac1(&C,&my_class::f1);
	aos::ClassOrFunctionDelegator<int> ac2(&C,&my_class::f2);
	aos::ClassOrFunctionDelegator<> af1(my_function);
	aos::ClassOrFunctionDelegator<int> af2(my_function_1);

	af1.call();
	af2.call(10);
	
	ac1.call();
	ac2.call(10);

	cout << "---------------------"<<endl;
	auto lmbd = [](int x){cout << __PRETTY_FUNCTION__ << ", x ="<<x <<endl;};
	aos::ClassOrFunctionDelegator<int> lmd(&lmbd);
	//lmbd();
	lmd.call(10);

	//pt<decltype(aos::declval<decltype(lmbd)&>()(10) )>();
	cout << "-------call char *------"<<endl;
	int arg = 123;
	char * argp = reinterpret_cast<char*>(&arg);
	typedef aos::make_index_sequence<0> IS;
	
	f1.vcall(argp);
	f2.vcall(argp);
	c1.vcall(argp);
	c2.vcall(argp);
	cout << "---------------------"<<endl;
	af1.vcall(argp);
	af2.vcall(argp);
	ac1.vcall(argp);
	ac2.vcall(argp);

	cout << "-------call char *------"<<endl;
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&f1.vcall),reinterpret_cast<char *>(&f1),argp);
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&f2.vcall),reinterpret_cast<char *>(&f2),argp);
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&c1.vcall),reinterpret_cast<char *>(&c1),argp);
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&c2.vcall),reinterpret_cast<char *>(&c2),argp);
	cout << "---------------------"<<endl;
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&af1.vcall),reinterpret_cast<char *>(&af1),argp);
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&af2.vcall),reinterpret_cast<char *>(&af2),argp);
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&ac1.vcall),reinterpret_cast<char *>(&ac1),argp);
	aos::call_delayed_function(reinterpret_cast<aos::VDELEGATORFUNCTYPE>(&ac2.vcall),reinterpret_cast<char *>(&ac2),argp);
	return 0;
}