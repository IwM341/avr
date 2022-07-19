#include <iostream>

class pubA{
	public: 
	int x;
	
	pubA(int x = 10):x(x){}
	int f(){return x;}
};
class privA{
	private: 
	int x;
	
	
	public:
	privA(int x = 10):x(x){}
	int f(){return x;}
};
class protA{
	protected: 
	int x;
	
	
	public:
	protA(int x = 10):x(x){}
	int f(){return x;}
};


class B: public privA{
	public:
	B(int x = 20): privA(x){}
	
	public:
	void print(){std::cout << x <<std::endl;}
};

int main(void){
	B a;
	a.print();	
	//std::cout << a.x <<std::endl;
	return 0;
}