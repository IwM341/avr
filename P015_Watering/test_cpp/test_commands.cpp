#include <iostream>
#include <string_view>
#include "../WaterWindow/Watering/Watering/include/parsing.h"
#include "../WaterWindow/Watering/Watering/global.h"

int main(void){
	typedef std::string_view string_view_std;
	using namespace Std;
	auto S = "  1:32:43-45  "sv; 
	hh_mm_ss_dd m_time;
	
	std::cout << "error code: " << (int)parse_hh_mm_dd(S,m_time) << std::endl;
	std::cout << m_time.days << "#" <<(int) m_time.hh << ":" << (int)m_time.mm << ":" <<(int) m_time.ss << std::endl;

	return 0;
}