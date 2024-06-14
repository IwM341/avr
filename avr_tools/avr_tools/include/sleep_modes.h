/*
 * sleep_modes.h
 *
 * Created: 09.04.2023 11:41:44
 *  Author: MainUser
 */ 


#ifndef SLEEP_MODES_H_
#define SLEEP_MODES_H_

#include "guard.h"
namespace aos{
	
	/**
	\brief structure, which contains information, about how many classes(processes) don't allow sleep
	*/
	struct sleep_block{
		enum smode:uint8_t{
			mode0 = 0,///<full sleep
			mode1 = 1,///sleep1
			mode2 = 2 /// sleep2
		};
		uint8_t _num_of_processes[3];
		__guard g;
		
		/**
		\brief increment  number of items, deprecated sleep in mode mode
		*/
		template <smode mode>
		inline void block(){_num_of_processes[mode]++;}
		/**
		\brief deincrement  number of items, deprecated sleep in mode mode
		*/
		template <smode mode>
		inline void unblock(){
			if(_num_of_processes[mode])
				_num_of_processes[mode]--;
		}
		
		inline void block(smode mode){
			g.lock();
			_num_of_processes[mode]++;
			g.unlock();
		}
		inline void unblock(smode mode){
			g.lock();
			if(_num_of_processes[mode])
			_num_of_processes[mode]--;
			g.unlock();
		}
		
		/**
		\brief check, if sleep mode is enabled
		\tparam mode sleep mode to check
		*/
		template <smode mode>
		inline bool is_enabled()const{return !_num_of_processes[mode];}
		/**
		\brief check, if sleep mode is enabled
		\param mode sleep mode to check
		*/
		inline bool is_enabled(smode mode)const{return !_num_of_processes[mode];}
	};
};


#endif /* SLEEP_MODES_H_ */