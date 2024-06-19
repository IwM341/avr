#pragma once

#include "include/ports.h"

template <uint8_t pin_manage,uint8_t pin_state>
struct Pump{
	pins::pin<pin_manage> m_manage;
	pins::pin<pin_manage> m_out_of_water;
	Pump():m_manage(pins::OutputMode),m_out_of_water(pins::InputMode){}
		
	inline void water(){
		m_manage.Write_1();
	}
	
	inline void stop(){
		m_manage.Write_0();
	}
	
	inline void on_out_of_water(){
		stop();
	}
	
	bool is_out_of_water() const{
		if(m_manage.Read() && !m_out_of_water.Read()){
			return true;
		}
		else {
			return false;
		}
	}
};