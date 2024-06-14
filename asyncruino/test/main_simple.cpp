#define F_CPU 16000000UL
#define ASYNCRUINO_UART_ENABLE

#define ASYNCRUINO_TIMER0_ENABLE
#define ASYNCRUINO_TIMER0_MAX_LISTENERS 1

#include <coroutine>
#include <stdlib.h>

#include <arduino/coro.h>
#include <arduino/usart.h>
#include <arduino/timers_hw.h>
asyncruino::task EchoServer(){
	asyncruino::uart::init(asyncruino::uart::BAUD_9600);
	
	while(1){
		char c = co_await asyncruino::uart::ReadByte();
		co_await asyncruino::uart::WriteByte(c);
	}
};

asyncruino::task Blink(uint16_t delay_ms,int pin){
	DDRD = 0x00;
	DDRB = 0xFF;
	auto & m_timer = asyncruino::timer0::instance();	
	while(1){		
		PORTB = 0x00;
		co_await m_timer.Delay(delay_ms,asyncruino::tl::ms);
		PORTB = 0xFF;
		co_await m_timer.Delay(delay_ms,asyncruino::tl::ms);
	}
}
int main(void)
{
	auto f = EchoServer();
	auto g = Blink(1000,0);
	return asyncruino::scheduler::run();
}

