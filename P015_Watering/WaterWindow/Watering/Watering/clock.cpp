#include "global.h"
#include "include/pair.h"

void start_clock(){
	clocks.value.set_tacts_per_count(256UL * 1024);
	TCCR0A = 0; 
	TCCR0B = (1 << CS00) | (1 << CS02); //prescalar 1024
	TIMSK0 = (1 << TOIE0);
};


void update_clock(void *){
	while(1){
		vTaskDelay(200);
		
		Std::pair<uint_least32_t,uint_least32_t> days= 
			clocks.apply([](Clocks & clk)
		{
			auto prv_day = clk.days;
			clk.update();
			auto m_day = clk.days;
			return Std::make_pair(m_day,prv_day);
		});  
		
		while( days.first > days.second){
			NextDayUpdatePlans();
			days.first--;
		}			
	}
}

ISR(TIMER0_OVF_vect){
	clocks.value.tick();
}