#include <iostream>
#include "../avr_tools/include/signals.h"
#include <thread>
#include <signal.h>
#include <unistd.h>

using namespace std; 

void f(int x){
	cout << "f(x = " << x << ")" << endl;
}

struct signal_emitter{
	aos::signal<int> my_signal;
	void emit_function(){
		emit my_signal(42);
	}
};

struct signal_getter{
	void my_slot(int x){
		cout << "signal recieved, " << x << endl;
		aos::event_loop::instance()->terminate();
	}
};

static signal_emitter S1;

void my_sig(int x){
    const_cast<signal_emitter &>(S1).emit_function();
}
int main(void){

	cout << "version 14" << endl;
	
	
	signal_getter S2;
	aos::connect(&S1.my_signal,&S2,&S2.my_slot);

	aos::dc_signal<void(int)> S;

	std::thread Th([](){
		int summ = 0; 
		for(size_t i=0;i<10000000000;++i){
			summ += 1;
		}
		my_sig(summ);
	});
	//S1.emit_function();

	signal(SIGINT,my_sig);
    //alarm(10);

	aos::event_loop::instance()->run();
	Th.join();
	return 0;
}