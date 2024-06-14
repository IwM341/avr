/*
 * coro.cpp
 *
 * Created: 06.09.2023 18:09:27
 * Author : MainUser
 */ 

#define F_CPU 16000000
#define ASYNCRUINO_UART_ENABLE

#define ASYNCRUINO_DOUBLE_LOCK_DEBUG
#define ASYNCRUINO_TIMER0_ENABLE
#define ASYNCRUINO_TIMER0_MAX_LISTENERS 1

#include <avr/io.h>
#include <coroutine>
#include <stdlib.h>
#include <arduino/coro.h>
#include <arduino/usart.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string_view>


#include <arduino/timers_hw.h>

#define min(a,b) ((a)>(b) ? (b) : (a))
#define max(a,b) ((a)<(b) ? (b) : (a))

template <typename T>
uint8_t write_int(T x,char * out,uint8_t max_len = 20){
	uint8_t len = 0;
	if(x < 0){
		*out = '-';
		++out;
		len++;
		x = -x;
	}
	if(x == 0){
		*out = '0';
		return 1;
	}
	char m_buf[20];
	uint8_t i = 0;
	while(x && i<max_len){
		auto dig = x%10;
		x /= 10;
		m_buf[i] = 	dig + '0';
		++i;
		len++;
	}
	for(uint8_t i=1;i<=len;++i){
		*out = m_buf[len-i];
		out++;
	}
	return len;
}

asyncruino::task EchoServer(){
	asyncruino::uart::init(asyncruino::uart::BAUD_9600);
	
	uint32_t x = __cplusplus;
	char x_str[10] = {'*','*','*','*','*','*','*','*','*','*'};
	write_int(x,x_str,10);
	co_await asyncruino::uart::WriteBytes(x_str,10);
	while(1){
		uint32_t m_delay = asyncruino::timer0::instance().m_list[0].sch;
		auto m_len = write_int(m_delay,x_str);
		co_await asyncruino::uart::WriteBytes(x_str,min(m_len,10));
		co_await asyncruino::uart::WriteByte('\n');
		
		uint32_t m_ticks_per_sec = asyncruino::timer0::instance().m_counter.tick_per_prefix_sec;
		m_len = write_int(m_ticks_per_sec,x_str);
		co_await asyncruino::uart::WriteBytes(x_str,min(m_len,10));
		co_await asyncruino::uart::WriteByte('\n');
		
		char c = co_await asyncruino::uart::ReadByte();
		char c1 = co_await asyncruino::uart::ReadByte();
		co_await asyncruino::uart::WriteByte(c);
		co_await asyncruino::uart::WriteByte(c1);
		//co_await asyncruino::uart::WriteByte('\n');
		
		uint8_t rd = co_await asyncruino::uart::ReadBytesUntil(x_str,'\n',10);
		if(rd == 10){
			co_await asyncruino::uart::WriteBytes("expect '\\n'\n");
		} else {
			co_await asyncruino::uart::WriteBytes(x_str,rd);
		}
	}
};

asyncruino::task Blink(uint16_t delay_ms,int pin){
	auto & m_timer = asyncruino::timer0::instance();	
	while(1){		
		PORTB = 0x00;
		co_await m_timer.Delay(delay_ms,asyncruino::tl::ms);
		PORTB = 0xFF;
		co_await m_timer.Delay(delay_ms,asyncruino::tl::ms);
	}
}



size_t delay_bug_param = 0;
volatile bool error = false;
void sleep_func (void){
	
	
	if(!(SREG & (1<<7)) ){
		asyncruino::uart::debug_crush("sreg became 0 strange!!!");
		error = true;
	}
	while(error){
		_delay_ms(100);
		PORTB = 0x00;
		_delay_ms(100);
		PORTB = 0xFF;
	}
	//sei();
}



void double_locked(){
	asyncruino::uart::debug_crush("twice lock");
}

void double_unlocked(){
	error = true;
	asyncruino::uart::debug_crush("twice unlock");
}

int main(void)
{	
	
	DDRD = 0x00;
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	for(uint8_t i=0;i<2;++i){
		//_delay_ms(100);
		PORTB = 0x00;
		//_delay_ms(100);
		PORTB = 0xFF;
	}
	
	
    /* Replace with your application code */
	auto f = EchoServer();
	auto g = Blink(1000,0);
	std::is_same_v<int,int>;
	asyncruino::scheduler::instance().sleep = sleep_func;
    return asyncruino::scheduler::run();
}

