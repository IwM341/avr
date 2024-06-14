#include <iostream>
#include <bitset>
#include <functional>
#include "interrupt_debug.h"
#include "../avr_tools/include/timer.h"

typedef aos::global_timer<uint8_t,4,4,0,0> m_timer_class;

using namespace std;
void int_handler(int id){
	//cout << "will process tick" << endl;
	aos::gtimer<m_timer_class>.process_tick();
}


void print_hello(){
	cout << "subscribe hello" << endl;
}
void print_world(){
	cout << "subscribe world" << endl;
}
void print_1(){
	cout << "alarm 1" << endl;
}

void my_sleep_function(aos::sleep_block * ){
	cout << "pausing system" << endl;
	sei();
	pause();
	cout << "awake system" << endl;
}


int main(void){
	std::cout<<"Hello"<<std::endl;
	interrupt_processor = int_handler;
	sei();
	init_alarm();
	
	std::function<void()> F1 = [](){cout << "direct subscribe hello"<<endl;};
	std::function<void()> F2 = [](){cout << "direct subscribe  world"<<endl;};
	std::function<void()> F3 = [](){cout << "direct alarm  world"<<endl;};
	
	std::function<void()> F4 = [](){cout << "soft subscribe hello"<<endl;};
	std::function<void()> F5 = [](){cout << "soft subscribe  world"<<endl;};
	std::function<void()> F6 = [](){cout << "soft alarm  world"<<endl;};

	cout << std::bitset<8>(SREG) << endl;

	auto & m_timer =  aos::gtimer<m_timer_class>;

	cout << "going to subscribe" << endl;
	m_timer.subscribe_d(1,&F1);
	cout << "subscribe 1" << endl;
	m_timer.subscribe_d(2,&F2);
	cout << "subscribe 2" << endl;
	m_timer.alarm_d(2,&F3);
	cout << "alarm " << endl;
	cout << std::bitset<8>(SREG) << endl;

	m_timer.subscribe_s(1,&F4);
	m_timer.subscribe_s(2,&F5);
	m_timer.alarm_s(2,&F6);


	//int_handler(1);
	//int_handler(1);
	//int_handler(1);
	//int_handler(1);
	////int_handler(1);
	//int_handler(1);
	aos::event_loop::instance()->sleep_function = my_sleep_function;
	aos::event_loop::instance()->run();
	return 0;
}