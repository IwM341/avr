#include <iostream>
#include "../include/core/scheduler.h"
#include "../include/core/simple_timer.h"
#include "../include/core/async_io.h"
#include <mutex>
#include <thread>
#include <sstream>
struct task
{
    struct promise_type
    {
        task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

template <asyncruino::InputStream stream_t>
task Echo(stream_t & m_input){
	int i = 0;
	char buf[10];
	while(1){
		/*
		i = rand()%10;
		char c = co_await m_input.ReadByte();
		std::stringstream S;
		S << "read c = '" << c <<"'" << std::endl;
		std::cout << S.str();
		co_await m_input.ReadBytes(buf,i);
		std::stringstream S1;
		S1 << "read str with size "<< i << " : '" << std::string_view(buf,i) <<"'"<<std::endl;
		std::cout << S1.str();
		*/
		size_t m_until1 = co_await m_input.ReadBytesUntil(buf,10,'q');
		std::stringstream S2;
		S2 << "until(1) with size "<< m_until1 << " : '" << std::string_view(buf,m_until1) <<"'"<<std::endl;
		std::cout << S2.str();
	
		size_t m_until2= co_await m_input.ReadBytesUntil(buf,10,"qw");
		std::stringstream S3;
		S3 << "until(2) with size "<< m_until2 << " : '" << std::string_view(buf,m_until2) <<"'"<<std::endl;
		std::cout << S3.str();
	}
}

int main(void){
	asyncruino::scheduler_impl<std::mutex,64> my_sheduler;
	asyncruino::async_input_impl<decltype(my_sheduler),std::mutex,size_t,64> m_input(my_sheduler);

	auto interrupt_tread = [&]{
		std::string x;
		while(1){
			std::cout << "input char:" << std::endl;
			std::getline(std::cin,x);
			for(auto c: x){
				m_input.interrupt(c);
			}
			
		} 
		std::terminate();
	};
	std::thread ith(interrupt_tread);

	auto f = Echo(m_input);

	my_sheduler.run();
	ith.join();
	return 0;
}