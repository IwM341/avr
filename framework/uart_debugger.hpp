#ifndef UART_DEBUGGER_HPP
#define UART_DEBUGGER_HPP

#include "uart_process.hpp"
#include "interrupt_mutex.hpp"




char c_num(uint8_t x){
	return (x<10 ? x + '0' :x + 'A'-10);
}

struct uart_ostream{
	inline uart_ostream & operator << (char c){
		uart::uart_process_r().write(c);
		return *this;
	}
	
	typedef enum :uint8_t {
		hex = 16,
		bin = 2,
		dec = 10
	} num_base;
	
	num_base m_base = dec;
	struct precesion{
		uint8_t prec;
		precesion(uint8_t prec):prec(prec){}
		precesion():prec(8){}
	};
	precesion m_precesion = 8;
	inline uart_ostream & operator << (num_base base){
		m_base  = base;
		return *this;
	}
	inline uart_ostream & operator << (precesion float_precesion){
		m_precesion  =  float_precesion;
		return *this;
	}
	
	inline uart_ostream & operator << (const char * str){
		uart::uart_process_r().write(str);
		return *this;
	}
	
	inline uart_ostream & operator << (uint8_t num){
		uint8_t MAX_BASE = 100;
		uint8_t denumerator = 10;
		
		switch(m_base){
			case dec:{
				MAX_BASE = 100;
				denumerator = 10;		
				break;
			}
			case hex:{
				MAX_BASE = 16;
				denumerator = 16;
				uart::uart_process_r().write("0x");
				break;
			}
			case bin:{
				MAX_BASE = 128;
				denumerator = 2;
				uart::uart_process_r().write("0b");
				break;
			}
		}
			
		
		
		char c  = num/MAX_BASE;
		num%=MAX_BASE;
		
		for(;MAX_BASE != 0 && c == 0;MAX_BASE /= denumerator){
			c = num/MAX_BASE;
			num%=MAX_BASE;
			if(m_base != dec){
				uart::uart_process_r().write(c_num(c));
			}
		}
		
		uart::uart_process_r().write(c_num(c));
		for(;MAX_BASE != 0;MAX_BASE /= denumerator){
			c = num / MAX_BASE;
			num %= MAX_BASE;
			uart::uart_process_r().write(c_num(c));
		}
		return *this;
	}
	inline uart_ostream & operator << (int8_t num){
		if(num < 0){
			uart::uart_process_r().write('-');
			num = -num;
		}
		return operator << ((uint8_t)num);
	}
	
	
	
	inline uart_ostream & operator << (uint16_t num){
		uint16_t MAX_BASE= 10000;
		uint8_t denumerator= 10;
		switch(m_base){
			case dec:{
				MAX_BASE = 10000;
				denumerator = 10;
				break;
			}
			case hex:{
				MAX_BASE = 4096;
				denumerator = 16;
				uart::uart_process_r().write("0x");
				break;
			}
			case bin:{
				MAX_BASE = 32768;
				denumerator = 2;
				uart::uart_process_r().write("0b");
				break;
			}
		}
		
		
		
		char c  = num/MAX_BASE;
		num%=MAX_BASE;
		
		for(;MAX_BASE != 0 && c == 0;MAX_BASE /= denumerator){
			c = num/MAX_BASE;
			num%=MAX_BASE;
			if(m_base != dec){
				uart::uart_process_r().write(c_num(c));
			}
		}
		
		uart::uart_process_r().write(c_num(c));
		for(;MAX_BASE != 0;MAX_BASE /= denumerator){
			c = num / MAX_BASE;
			num %= MAX_BASE;
			uart::uart_process_r().write(c_num(c));
		}
		
		return *this;
	}
	inline uart_ostream & operator << (int16_t num){
		if(num < 0){
			uart::uart_process_r().write('-');
			num = -num;
		}
		return operator << ((uint16_t)num);
	}
	
	inline uart_ostream & operator << ( uint32_t num){
		uint32_t MAX_BASE= 1000000000 ;
		uint8_t denumerator= 10;
		
		switch(m_base){
			case dec:{
				MAX_BASE = 1000000000;
				denumerator = 10;
				break;
			}
			case hex:{
				MAX_BASE = 268435456;
				denumerator = 16;
				uart::uart_process_r().write("0x");
				break;
			}
			case bin:{
				MAX_BASE = 2147483648;
				denumerator = 2;
				uart::uart_process_r().write("0b");
				break;
			}
		}
		
		
		
		char c  = num/MAX_BASE;
		num%=MAX_BASE;
		
		for(;MAX_BASE != 0 && c == 0;MAX_BASE /= denumerator){
			c = num/MAX_BASE;
			num%=MAX_BASE;
			if(m_base != dec){
				uart::uart_process_r().write(c_num(c));
			}
		}
		
		uart::uart_process_r().write(c_num(c));
		for(;MAX_BASE != 0;MAX_BASE /= denumerator){
			c = num / MAX_BASE;
			num %= MAX_BASE;
			uart::uart_process_r().write(c_num(c));
		}
		return *this;
	}
	inline uart_ostream & operator << (int32_t num){
		if(num < 0){
			uart::uart_process_r().write('-');
			num = -num;
		}
		return operator << ((uint32_t)num);
	}
	
	inline uart_ostream & operator << (float num){
		if(num < 0)
			num = - num;
		
		uint16_t exponent = 0;
		while(num >= 10){
			exponent ++;
			num /= 10;
		}
		while(num < 1){
			exponent --;
			num *= 10;
		}
		
		uart::uart_process_r().write(c_num(num));
		num -= (uint8_t)(num);
		uart::uart_process_r().write(c_num('.'));
		
		uint16_t MAX_BASE = 1;
		
		for(uint16_t i=0;i<m_precesion.prec;++i){
			MAX_BASE *= 10;
		}
		uint32_t inum = num*MAX_BASE;
		MAX_BASE /= 10;
		
		for(;MAX_BASE != 0;MAX_BASE /= 10){
			uart::uart_process_r().write(c_num(inum/MAX_BASE));
			inum %= MAX_BASE;
		}
		
		return *this;
	}
	
	
	
	inline static uart_ostream & instance(){
		static uart_ostream S;
		return S;
	}
	inline static uart_ostream * instance_p(){
		return &uart_ostream::instance();
	}
	
	
	private:
	uart_ostream(){}
	uart_ostream(const uart_ostream &){}
	uart_ostream(uart_ostream &&){}
		
};

static uart_ostream & cout = uart_ostream::instance();
const char endl = '\n';

#ifndef RELEASE
#define debug(x) cout << x << endl;
#else 
#define debug(x)
#endif

#ifndef RELEASE
inline void __print(){
	cout << endl;
}

template <typename T,typename...Args>
inline void __print(const T & first,const Args&...Others){
	cout << first;
	__print(Others...);
}
#else
#define __print(x)
#endif

template <typename...Args>
inline void print(Args...args){
	INTERRUPT_LOCK
	__print(args...);
	INTERRUPT_UNLOCK
}

#endif

