#include <iostream>

struct TimerParams{
	uint8_t OCRA;
	uint8_t CS;	
};
#define difference(a,b) ((a) > (b) ? ( (a) - (b)) : ((b)-(a)))

//F_OCRA = F_CPU/(2*N*(1+OCRA))

constexpr TimerParams bestTimerParams(uint32_t f_cpu,uint32_t f_target){
	uint32_t best_delta = -1;
	
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

int main(void){
	
	TimerParams TP = bestTimerParams(16000000,1000);
	std::cout << "TP.bestCS = " << (size_t)TP.CS << ", " << "TP.bestOCRA = " << (size_t)TP.OCRA << std::endl;
	return 0;
}