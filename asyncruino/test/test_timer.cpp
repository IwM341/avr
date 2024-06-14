#include <iostream>
#include "../include/core/scheduler.h"
#include "../include/core/simple_timer.h"
#include <mutex>
#include <thread>
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

template <asyncruino::TimerCounter Timer_t>
task Timered(Timer_t & m_timer,int m_delay){
	int i = 0;
	while(1){
		++i;
		co_await m_timer.Delay(m_delay);
		std::cout <<"\nTimer" << m_delay << " : "<<  i << std::endl;
		if(!(i%4)){
			using namespace asyncruino::time_literals;
			std::cout << ("delayed " + std::to_string(m_timer.current()) + " ms") <<std::endl;
			std::cout << ("delayed " + std::to_string(m_timer.current(ps)) + " ps") <<std::endl;
			std::cout << ("delayed " + std::to_string(m_timer.current(ns)) + " ns") <<std::endl;
			std::cout << ("delayed " + std::to_string(m_timer.current(mus)) + " mus") <<std::endl;
			std::cout << ("delayed " + std::to_string(m_timer.current(ms)) + " ms") <<std::endl;
			std::cout << ("delayed " + std::to_string(m_timer.current(s)) + " s") <<std::endl;
		}
	
	}
}

int main(void){
	asyncruino::scheduler_impl<std::mutex,64> my_sheduler;
	asyncruino::timer_counter_impl<decltype(my_sheduler),std::mutex> 
		m_timer(my_sheduler,1,asyncruino::time_literals::ms);

	m_timer.interrupt();
	std::cout << m_timer.current(asyncruino::time_literals::mus) << "mus" << std::endl;
	std::cout << m_timer.current(asyncruino::time_literals::ms) << "ms" << std::endl;
	std::cout << m_timer.current(asyncruino::time_literals::ns) << "ns" << std::endl;

	std::cout << m_timer.m_counter.to_counter_t(10,asyncruino::time_literals::mus) << std::endl;
	std::cout << m_timer.m_counter.to_counter_t(1,asyncruino::time_literals::s) << std::endl;

	auto interrupt_tread = [&]{
		char x;
		while(1){
			std::cout << "interrupt" << " me: ";
			std::cin >> x;
			if(x == 'q'){
				std::cout << "exit" << std::endl;
				break;
			} else {
				m_timer.interrupt();
			}
		} 
		std::terminate();
	};
	std::thread ith(interrupt_tread);

	auto f = Timered(m_timer,1);
	auto g = Timered(m_timer,2);

	my_sheduler.run();
	ith.join();
	return 0;
}