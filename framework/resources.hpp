#ifndef RESOURCES_H
#define RESOURCES_H

#include "delegator.hpp"

#define PORTD_RESTRICT 0b00000000
#define PORTB_RESTRICT 0b11100000
#define PORTC_RESTRICT 0b11100000
#define ANALOG_RESTRICT 0b11100000
#define TIMERS_RESTRICT 0b11111000


#ifndef RES_TIMER_LIST_SIZE
#define RES_TIMER_LIST_SIZE 4;
#endif

#ifndef RES_PORTS_LIST_SIZE
#define RES_PORTS_LIST_SIZE 4;
#endif


#ifndef RES_ANALOG_LIST_SIZE
#define RES_ANALOG_LIST_SIZE 4;
#endif



struct atmega328p_resources{
	uint8_t _PORTD;
	uint8_t _PORTB;
	uint8_t _PORTC;
	
	uint8_t _Analog;
	uint8_t _Timers;
	
	#ifdef TIMER_FREE_METACALL
	std::list<AbstractDelegator<uint8_t>*> timer_calls;
	#endif
	#ifdef PORTS_FREE_METACALL
	std::list<AbstractDelegator<uint8_t>*> ports_calls;
	#endif
	#ifdef ANALOG_FREE_METACALL
	std::list<AbstractDelegator<uint8_t>*> analog_calls;
	#endif
	
	private:
	
	atmega328p_resources():_PORTD(0),_PORTB(0),_PORTC(0),_Analog(0),_Timers(0){}
	atmega328p_resources(const atmega328p_resources &) = delete;
	atmega328p_resources(atmega328p_resources &&) = delete;
	
	public:
	static atmega328p_resources& instance_r(){
		static atmega328p_resources A;
		return A;
	}
	static atmega328p_resources* instance_p(){
		return &instance_r();
	}
	
	
	
	
	/*try to occupy port. if success returns 1, else 0*/
	bool occupyPort(uint16_t portName,uint8_t mask){
		if(portName == PORTD){
			if(_PORTD & mask){
				return false;
			}
			else{
				_PORTD |= mask;
			}
		}
		else if(portName == PORTB){
			if( (_PORTB & mask) || (mask & PORTB_RESTRICT)){
				return false;
			}
			else{
				_PORTB |= mask;
			}
		}
		else if(portName == PORTC){
			if( (_PORTC & mask) || (mask & PORTC_RESTRICT)){
				return false;
			}
			else{
				_PORTC |= mask;
			}
		}
		else{
			return false;
		}
	}
	/*try to occupy port. if success returns 1, else 0*/
	void freePort(uint16_t portName,uint8_t mask){
		if(portName == PORTD){
			_PORTD &= ~mask;
		}
		else if(portName == PORTB){
			mask = mask & ~PORTB_RESTRICT;
			_PORTB &= ~mask;
		}
		else if(portName == PORTC){
			mask = mask & ~PORTC_RESTRICT;
			_PORTC &= ~mask;
		}
		portFree(portName);
	}
	
	bool occupyTimer(uint8_t timer){
		uint8_t mask = 1 << timer;
		if(_Timers & mask){
			return false;
		}
		else{
			_Timers |= mask;
		}
	}
	void freeTimer(uint8_t timer){
		_Timers &= ~(1 << timer);
		timerFree(timer);
	}
	
	bool occupyAnalog(uint8_t analog_port_num){
		uint8_t mask = 1 << analog_port_num;
		if(_Analog & mask){
			return false;
		}
		else{
			_Analog |= mask;
		}
	}
	void freeAnalog(uint8_t analog_port_num){
		_Analog &= ~(1 << analog_port_num);
		analogFree(analog_port_num);
	}
	
	inline void timerFree(uint8_t timer);
	inline void portFree(uint8_t port);
	inline void analogFree(uint8_t analog_port_num);
	
	#ifdef TIMER_METACALL
	template <typename...FunctionInfo>
	bool connectTimerFree(FunctionInfo...fInfo){
		auto Delegate = DelegatorConstructor<uint8_t>::Construct(fInfo...);
		for(auto it = timer_calls.begin();it != timer_calls.end();++it){
			if( (*it)->isSame(Delegate)){
				delete Delegate;
				return 0;
			}	
		}
		timer_calls.push_back(Delegate);
		return true;
	}
	#endif
	
	#ifdef PORTS_METACALL
	template <typename...FunctionInfo>
	bool connectPortsFree(FunctionInfo...fInfo){
		auto Delegate = DelegatorConstructor<uint8_t>::Construct(fInfo...);
		for(auto it = ports_calls.begin();it != ports_calls.end();++it){
			if( (*it)->isSame(Delegate)){
				delete Delegate;
				return 0;
			}
		}
		ports_calls.push_back(Delegate);
		return true;
	}
	#endif

	#ifdef ANALOG_METACALL
	template <typename...FunctionInfo>
	bool connectAnalogFree(FunctionInfo...fInfo){
		auto Delegate = DelegatorConstructor<uint8_t>::Construct(fInfo...);
		for(auto it = analog_calls.begin();it != analog_calls.end();++it){
			if( (*it)->isSame(Delegate)){
				delete Delegate;
				return 0;
			}
		}
		analog_calls.push_back(Delegate);
		return true;
	}
	#endif
	
	
	/**DISCONNECT*/
	
	#ifdef TIMER_METACALL
	template <typename...FunctionInfo>
	void disconnectTimerFree(FunctionInfo...fInfo){
		auto Delegate = CreateDelegateFromArgs(fInfo...);
		timer_calls.remove_if([](AbstractDelegator * D){return D->isSame(Delegate);});
		delete Delegate;
	}
	#endif
	
	#ifdef PORTS_METACALL
	template <typename...FunctionInfo>
	bool connectPortsFree(FunctionInfo...fInfo){
		auto Delegate = CreateDelegateFromArgs(fInfo...);
		ports_calls.remove_if([](AbstractDelegator * D){return D->isSame(Delegate);});
		delete Delegate;
	}
	#endif

	#ifdef ANALOG_METACALL
	template <typename...FunctionInfo>
	bool connectAnalogFree(FunctionInfo...fInfo){
		auto Delegate = CreateDelegateFromArgs(fInfo...);
		analog_calls.remove_if([](AbstractDelegator * D){return D->isSame(Delegate);});
		delete Delegate;
	}
	#endif
	
	
	
	
};

#ifndef EXTERN_TIMER_FREE_SLOT
#ifndef TIMER_METACALL
void atmega328p_resources::timerFree(uint8_t){}
#endif
#endif

#ifndef EXTERN_ANALOG_FREE_SLOT
#ifndef PORTS_METACALL
void atmega328p_resources::portFree(uint8_t){}
#endif
#endif

#ifndef EXTERN_PORT_FREE_SLOT
#ifndef ANALOG_METACALL
void atmega328p_resources::analogFree(uint8_t){}
#endif
#endif



#endif