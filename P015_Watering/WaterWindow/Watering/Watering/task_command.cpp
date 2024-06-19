#include "global.h"
#include "include/type_traits.h"
#include "../Uart/HardwareSerial.h"
#include "include/string_filter.h"
#include "include/string_view.h"
#include "include/parsing.h"
void save_impl();

enum class float_pname: uint8_t{
	Temp = 0,
	T1o = 1,
	T1c = 2,
	T2o = 3,
	T2c = 4
};
enum class uint32_pname{
	Tmd = 0,
	Twd = 1,
	f_cpu = 2
};

float get_float_param(float_pname pname);
uint_least32_t get_uint32_param(uint32_pname pname);

void print_plan();
void print_every();

inline void print_sw(Std::string_view const &m_string){
	Serial.write(m_string.data(),m_string.size());
}
void print_clock(hh_mm_ss_dd const & m_time);

void task_command_executor(void *){
	constexpr uint8_t max_buf_size = 64;
	char strbuf[max_buf_size];
	Serial.begin(9600);
	while(1){
		
		uint8_t rd_bt = Serial.readBytesUntil('\n',strbuf,max_buf_size);
		//uint8_t rd_bt = 8;
		//memcpy(strbuf,"get Temp",8);
		Std::string_view m_string(strbuf,rd_bt);
		Std::string_view m_command = parse_command(m_string);
		if(m_command.size() == 0){
			char error_code[] = "error no command name";
			Serial.println(error_code);
		}
		
		
		
		if(m_command == "get"){
			using namespace Std;
			Std::array<Std::string_view ,5> float_params
			("Temp"sv,"T1o"sv,"T1c"sv,"T2o"sv,"T2c"sv);
			 
			Std::string_view m_pname = parse_variable(m_string);
			uint8_t is_float = float_params.find(m_pname);
			
			if(is_float <float_params.size() ){
				float m_param = get_float_param(static_cast<float_pname>(is_float));
				print_sw(float_params[is_float]);
				Serial.print(" = ");
				Serial.println(m_param);
				continue;
			}
			Std::array<Std::string_view ,3> int_params
				("Tmd"sv,"Twd"sv,"f_cpu"sv);

			uint8_t is_int = int_params.find(m_pname);
			if(is_int < int_params.size()){
				uint_least32_t m_param = get_uint32_param(static_cast<uint32_pname>(is_float));
				print_sw(int_params[is_int]);
				Serial.print(" = ");
				Serial.println(m_param);
				continue;
			}
			if(m_pname == "clock"){
				Serial.print("Time = ");
				print_clock(clocks.get([](Clocks const & clk){return clk.current();}));
				Serial.println();
				continue;
			}
			if(m_pname == "plan"){
				print_plan();
				continue;
			}
			if(m_pname == "every"){
				print_every();
				continue;
			}
			{
				char error_code[] = "unknown argument of command get";
				Serial.println(error_code);
			}
			continue;
		}
		
		end_loop:;
	}
}



void print_clock(hh_mm_ss_dd const & m_time){
	auto getNum1Num2 = [](uint8_t value)->Std::array<char,2>{
		uint8_t del = value/10;
		uint8_t rm = value%10;
		return {del%10+'0', rm+'0'};
	};
	constexpr uint8_t length = 9;
	char str[length];
	memcpy(str + 0,getNum1Num2(m_time.hh).data(),2);
	str[2] = ':';
	memcpy(str + 3,getNum1Num2(m_time.mm).data(),2);
	str[5] = ':';
	memcpy(str + 6,getNum1Num2(m_time.ss).data(),2);
	str[8] = 0;
	Serial.print(str);
}

#define SETTINGS_PARAM_CASE(pname) \
case float_pname::pname:\
	return settings.get([](Settings const & S){return S.pname;});\
	break;

float get_float_param(float_pname pname){
	switch (pname)
	{
	case float_pname::Temp:
		return Temp.get();
		break;
	SETTINGS_PARAM_CASE(T1o)
	SETTINGS_PARAM_CASE(T1c)
	SETTINGS_PARAM_CASE(T2o)
	SETTINGS_PARAM_CASE(T2c)
	default:
		return 0.0/0.0;
	}
}

#define SETTINGS_I_PARAM_CASE(pname) \
case uint32_pname::pname:\
	return settings.get([](Settings const & S){return S.pname;});\
	break;
uint_least32_t get_uint32_param(uint32_pname pname){
	switch (pname)
	{
		SETTINGS_I_PARAM_CASE(Tmd)
		SETTINGS_I_PARAM_CASE(Twd)
		SETTINGS_I_PARAM_CASE(f_cpu)
		default:
			return 0;
			break;
	}
}

void print_duration(uint_least32_t m_secs){
	hh_mm_ss_dd m_dur = hh_mm_ss_dd::from_sec(m_secs);
	if(m_dur.hh != 0)
	{
		Serial.print((int)m_dur.hh);
		Serial.print(" hours, ");
	}
	if(m_dur.mm != 0 )
	{
		Serial.print((int)m_dur.mm);
		Serial.print(" mins, ");
	}
	Serial.print((int)m_dur.ss);
	Serial.print(" secs");
}

void print_plan(){
	water_plan_array_t const& mplan = water_plan.value;
	uint8_t num = 0;
	for(uint8_t i=0;i<mplan.size();++i){
		if(mplan[i].actual){
			Serial.print((char) (num+'0'));
			Serial.print(')');
			Serial.print(" at ");
			print_clock(mplan[i].ptime);
			Serial.print(" , ");
			print_duration(mplan[i].duration);
			Serial.println();
			++num;
		}
	}
}
void print_every(){
	water_every_array_t const& m_every = water_every.value;
	uint8_t num = 0;
	for(uint8_t i=0;i<m_every.size();++i){
		if(m_every[i].exist_flag){
			Serial.print((char) (num+'0'));
			Serial.print(')');
			Serial.print("every ");
			print_clock(hh_mm_ss_dd(0,m_every[i].hh,m_every[i].mm,0));
			Serial.print(" , ");
			print_duration(m_every[i].duration);
			Serial.println();
			++num;
		}
	}
}