

#include <avr/io.h>
#include <stdlib.h>

volatile int sm = 0;

/*
struct promise;

struct coroutine : std::coroutine_handle<promise>
{
	using promise_type = ::promise;
};

struct promise
{
	coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
	std::suspend_always initial_suspend() noexcept { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }
	void return_void() {}
	void unhandled_exception() {}
};

auto MyCoro(){
	co_await 10;
}
*/
struct S{
	int x;
	char c;
};
int main(void)
{
	uint8_t x =  DDRD;
	volatile uint8_t y = __builtin_popcount(x);
	volatile size_t sizeof_S = sizeof(S);
	volatile size_t sizeof_size_t = sizeof(size_t);
	while(sizeof_S + sizeof_size_t + y){
		y += 1;
	}
}



