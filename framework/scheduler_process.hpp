#ifndef SCHEDULER_PROCES_H
#define SCHEDULER_PROCES_H

#include "delegator.hpp"
//#include "resources.hpp"
#include <avr/interrupt.h>
#include "data.hpp"


#define iabs(a) ((a) > 0 ? (a) : (-a))

#define difference(a,b) ((a) > (b) ? ( (a) - (b)) : ((b)-(a)))

struct TimerParams{
	uint8_t bestOCRA;
	uint8_t bestCS;	
};

constexpr TimerParams bestTimerParams(uint32_t f_cpu,uint32_t f_target){
	struct TimerParams TP{255,3};
	
	uint16_t divs[4] = {1,8,64,256};
	uint8_t bcs = 1;
	
	for(;bcs < 5 && (f_cpu/(f_target*2*divs[bcs-1])) >= 255;++bcs);
	
	uint16_t bocra = f_cpu/(f_target*2*divs[bcs-1]) - 1;
	
	if(f_cpu - (f_target*2*divs[bcs-1])*(bocra + 1) > (f_target*2*divs[bcs-1])*(bocra + 2) - f_cpu){
		bocra ++;
	}
	TP.OCRA = bocra;
	TP.CS = bcs;
	
	return TP;
}

constexpr uint64_t sec = 1000;
constexpr uint64_t min = 60*sec;
constexpr uint64_t hour = 60*min;
constexpr uint64_t day = 24*hour;


class scheduler{
	uint64_t _clock;
	
	struct _alarm{
		uint64_t alarm_clock;
		AbstractDelegator<> * Slot;
		_alarm(uint64_t alarm_clock,AbstractDelegator<> * Slot):alarm_clock(alarm_clock),Slot(Slot){}
	};
	
	list<_alarm> alarm_calls;
	public:
	struct _data{
		uint8_t days;
		uint8_t hours;
		uint8_t minuts;
		uint8_t seconds;
		uint8_t millis;
		
		operator uint64_t() const{
			return millis + seconds*sec+minuts*min+hours*hour + days*day;
		}
		_data(){}
		_data(uint64_t _clk){
			millis = _clk % 1000;
			_clk /= 1000;
			
			seconds = _clk % 60;
			_clk /= 60;
			
			minuts= _clk % 60;
			_clk /= 60;
			
			hours = _clk % 24;
			_clk /= 24;
			
			days = _clk;	
		}
	};
	
	
	void init(){
		TCCR0B |= (1<<WGM12);
		TIMSK0 |= (1<<OCIE0A);
		
		TimerParams TP = bestTimerParams(F_CPU,1000);
		OCR0A = TP.bestOCRA; //124
		TCCR0B |= TP.bestCS; //3
	}
	
	
	
	template <typename...FunctionInfo>
	void conect_by_delta_clock(uint64_t delta_clock,FunctionInfo...fInfo){
		alarm_calls.push_back(_alarm(delta_clock+_clock,DelegatorConstructor<>::Construct(fInfo...)) );
	}
	void timer_ocr_interrupt(){
		++_clock;
		for(auto it = alarm_calls.begin();it != alarm_calls.end();){
			if((*it).alarm_clock <= _clock ){
				(*it).Slot->call();
				delete (*it).Slot;
				it = alarm_calls.remove(it);
			}
			else
				++it;
		}
	}
	uint64_t clock() const{return _clock;}
	uint64_t data_clock() const{
		return _data(_clock);
	}
	void set_clock(const _data & dat){
		_clock = dat;
	}
	
	private:
	scheduler():_clock(0){}
	scheduler(const scheduler &) = delete;
	scheduler(scheduler &&) = delete;
	public:
	
	inline static scheduler & scheduler_r(){
		static scheduler S;
		return S;
	}
	inline static scheduler * scheduler_p(){
		return &scheduler_r();
	}
};

ISR(TIMER0_COMPA_vect){
	scheduler::scheduler_r().timer_ocr_interrupt();
}




#endif