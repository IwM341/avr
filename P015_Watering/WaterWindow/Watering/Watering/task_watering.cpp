#include "global.h"
#include "Pump.h"

void NextDayUpdatePlans(){
	water_plan.apply([](water_plan_array_t & plan){
			for(uint_least8_t i=0;i<plan.size();++i){
				if(plan[i].actual){
					plan[i].next_day();
				}
			}
		});
	
	water_every.apply([](water_every_array_t & every){
		for(uint_least8_t i=0;i<every.size();++i){
			if(every[i].exist_flag){
				every[i].next_day();
			}
		}
	});
}

hh_mm_ss_dd water_process(hh_mm_ss_dd const &current,uint32_t water_seconds_duration){
	hh_mm_ss_dd stop_time = current + water_seconds_duration;
	water_impl.water();
	while(1){
		vTaskDelay(1000);
		auto curr_time = clocks.get([](Clocks const & clk){return clk.current();});
		if(water_impl.is_out_of_water() || curr_time >= stop_time){
			water_impl.stop();
			return curr_time;
		}
	}
}

void task_watering(void *){
	hh_mm_ss_dd last_water = clocks.get([](Clocks const & clk){return clk.current();});
	
	while(1){
		vTaskDelay(1000);
		uint_least32_t m_delay = settings.get([](Settings const & S){return S.Twd;});
		hh_mm_ss_dd current = clocks.get([](Clocks const & clk){return clk.current();});
		bool ready = false;
		uint_least32_t duration = 0; 
		water_plan.apply([&current,&last_water,&ready,&duration,&m_delay](water_plan_array_t & plan){
			for (uint_least8_t i=0;i<plan.size();++i){
				if(plan[i].actual){
					if(plan[i].is_ready(current.hh,current.mm,current.ss)){
						if(last_water + m_delay < current || plan[i].force){
							ready = true;
							duration = plan[i].duration;
							plan[i].after_water();
						}
					}
				}
			}
		});
		if(ready){
			last_water = water_process(current,duration);
		}
		ready = false;
		water_every.apply([&current,&last_water,&ready,&duration,&m_delay](water_every_array_t & m_every){
			for (uint_least8_t i=0;i<m_every.size();++i){
				if(m_every[i].exist_flag){
					if(m_every[i].is_ready(current.hh,current.mm,current.ss)){
						if(last_water + m_delay  <= current){
							ready = true;
							duration = m_every[i].duration;
							m_every[i].after_water();
						}
					}
				}
			}
		});
		if(ready){
			last_water = water_process(current,duration);
		}
		
		
	}	
}