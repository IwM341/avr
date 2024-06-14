#include <iostream>
#include "../include/core/pipe.h"
#include "debugdef.hpp"
#include <queue>
#include <assert.h>
template <typename T,typename s_t,s_t res>
void print_state(const asyncruino::pipe<T,s_t,res> & P){

	for(s_t i=0;i<P.reserved;++i){
		if(i >= P._start){
			if(i < P._start+ P._size){
				std::cout << P._data[i];
			} else {
				std::cout << "_";
			}
		} else {
			if((P._start+P._size) > P.reserved &&
			 	i < (P._start+P._size)% P.reserved ){
				std::cout <<P._data[i];
			 }
			 else {
				std::cout <<"_";
			 }
		}
	}
	std::cout << std::endl;
}
template <typename T>
void print_queue(std::queue<T> & Q){
	size_t m_size = Q.size();
	for(size_t i=0;i<m_size;++i){
		T tmp = Q.front();
		Q.pop();
		Q.push(tmp);
		if((tmp>='0'&& tmp<='9') || (tmp>='a'&& tmp<='z') || (tmp>='A'&& tmp<='Z') )
			std::cout << tmp;
		else
			std::cout << '*';
	}
	print();
}

constexpr size_t WRITE_CHAR = 0;
constexpr size_t READ_CHAR = 1;
constexpr size_t WRITE_STR = 2;
constexpr size_t READ_STR = 3;



int main(void){
	constexpr size_t max_size = 30;
	asyncruino::pipe<char,size_t,max_size> P;
	std::queue<char> Pt;

	char c = '*';
	const char *buff_in = "0123456789abcdefghijklmnopqrstuvwxyz";
	const size_t in_len = strlen(buff_in);

	char buf0[64];
	char buf1[64];

	for(size_t i=0;i<1000;++i){
		assert(P.size() == Pt.size());
		//PVAR(i);
		//print_state(P);
		//print_queue(Pt);
		size_t m_action = (size_t)rand()%4;
		switch (m_action)
		{
		case WRITE_CHAR:
		{
			char c = buff_in[rand()%in_len];	
			if(P._size < max_size){
				assert(P.write(c));
				Pt.push(c);
				
			}
			break;
		}
		case READ_CHAR:
		{
			char c0,c1;
			if(P._size){
				assert(P.read(c0));
				c1 = Pt.front();
				Pt.pop();
				assert(c0 == c1);
			}
			break;
		}
		case WRITE_STR:
		{
			size_t m_size = rand()%in_len;
			if(m_size <= P.remain_space()){
				assert(P.write(buff_in,m_size));
				for(size_t i=0;i<m_size;++i){
					Pt.push(buff_in[i]);
				}
			}
			break;
		}
		case READ_STR:
		{
			assert(P.empty() == Pt.empty());
			size_t read_size = rand()%(P._size+5);
			if(!P.empty()){
				size_t rd = P.read(buf0,read_size);
				size_t rd1 = 0;
				for(; (rd1<read_size && !Pt.empty());++rd1){
					buf1[rd1] = Pt.front();
					Pt.pop();
				}
				assert(rd == rd1);
				assert(std::string_view(buf0,rd)==std::string_view(buf1,rd));
			}
			break;
		}
		default:
		{
			assert(false);
			break;
		}
		}
		assert(P._size == Pt.size());
		assert(P._start < P.reserved);
	}

	return 0;
}