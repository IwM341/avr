#ifndef IO_PROCESS_HPP
#define IO_PROCESS_HPP

#define slot
#define IO_QSIZE

#include "data.hpp"
#include "../framework/global.hpp"
struct IO_process{
	
	public:
	void open();
	bool write(uint8_t c);
	bool write(uint8_t buff_size,const uint8_t * buff);
	slot inline void data_recieve_interrupt(uint8_t data);
	
	void close();
};

#endif