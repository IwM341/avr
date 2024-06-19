#include <iostream>
#include <string_view>
#include "../WaterWindow/Watering/Watering/include/parsing.h"

enum class float_pname: uint8_t{
	Temp = 0,
	T1o = 1,
	T1c = 2,
	T2o = 3,
	T2c = 4
};
float get_float_param(float_pname pname){
	return static_cast<uint8_t>(pname);
}
int main(void){
	using namespace Std;
	char mbuf[20];
	memcpy(mbuf,"get Temp",8);
	Std::string_view m_string(mbuf,8);
	Std::string_view m_command = parse_command(m_string);
	if(m_command == "get"){
		using namespace Std;
		Std::array<Std::string_view ,5> float_params
			({"Temp"sv,"T1o"sv,"T1c"sv,"T2o"sv,"T2c"sv});
		Std::string_view m_pname = parse_variable(m_string);
		uint8_t is_float = float_params.find(m_pname);
		if(is_float <float_params.size() ){
			float m_param = get_float_param(static_cast<float_pname>(is_float));
			std::cout << float_params[is_float].data() << std::endl;
			std::cout << " = " <<std::endl;
			std::cout << m_param<<std::endl;
		}
	}
	return 0;
}

