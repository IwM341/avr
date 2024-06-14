#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <random>
#include <string.h>  
#include <cmath>
#include <vector>
#include <algorithm>
#include <exception>
#include "../avr_tools/include/pipe.h"

struct no_guard{
  inline void lock(){}
  inline void unlock(){}
};

using namespace std;


#define BUFF_SIZE 2000
void routine_print_string(char * dst,aos::pipe<uint8_t,std::mutex> *P){

	std::random_device rd;
    std::mt19937 mt(rd());
	std::uniform_int_distribution distrib(1567);


	char * ptr = dst; 
	while(ptr != dst + BUFF_SIZE){
		uint8_t rdread = distrib(mt)  % P->_reserved + 1;
		std::stringstream S;
		S << "trying to read " << (size_t)rdread << " bytes, dst-ptr = " << (dst+BUFF_SIZE-ptr)  << endl; 
		cout << S.str();


		auto dist = std::min<int>(rdread,BUFF_SIZE+dst-ptr);
		if(P->read(ptr,dist)){
			ptr += dist;
		}
		if((int)(dst+BUFF_SIZE-ptr)<0){
			throw std::runtime_error("negativee distance in main");
		}
	}
}


char src[BUFF_SIZE];
char *dst;

int main()
{

	char *buffer = new char[240];
    auto P = new aos::pipe<uint8_t,std::mutex>(buffer,240);
	dst = new char[BUFF_SIZE];
    
	for(size_t i=0;i<BUFF_SIZE;++i){
		src[i] = 'a' + i%('z'-'a');
	}
	src[BUFF_SIZE-1] = 0;

    std::thread Thr(routine_print_string,dst,P);

	std::random_device rd;
    std::mt19937 mt(rd());
	std::uniform_int_distribution distrib(1567);

	char * ptr = (src); 
	while(ptr != src + BUFF_SIZE){
		std::stringstream S;
		uint8_t rdwrite = distrib(mt)  % P->_reserved + 1;
		S << "trying to write " << (size_t)rdwrite << " bytes, src-ptr = " << (int)(src+BUFF_SIZE-ptr)  << endl;
		cout << S.str();


		auto last_ptr = ptr;
		//auto last_P = *P;

		auto dist = std::min<int>(rdwrite,BUFF_SIZE+src-ptr);
		if(P->write(ptr,dist)){
			ptr += dist;
		}
		if((int)(src+BUFF_SIZE-ptr)<0){
			throw std::runtime_error("negative distance in main");
		}
	}

	Thr.join();

	cout << boolalpha;
	cout << (bool)strcmp(src,dst) << endl;

	for(size_t i=0;i<BUFF_SIZE;++i){
		if(src[i] != dst[i]){
			cout << "bad i = "<< i << endl;
		}
	}

	cout << src << endl;
	cout << endl;
	cout << dst << endl;

    return 0;
}