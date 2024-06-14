/*
 * event_loop.h
 *
 * Created: 09.04.2023 11:47:42
 *  Author: MainUser
 */ 


#ifndef EVENT_LOOP_H_
#define EVENT_LOOP_H_
#include "pipe.h"
#include "size_types.h"
#include "guard.h"
#include "sleep_modes.h"
#include "signals.h"


#ifndef PIPE_SIZE
//#warning "auto define of PIPE_SIZE"
#define PIPE_SIZE 240
#endif

#ifndef ALLOW_SEND_ARGS
//#warning "auto define of ALLOW_SEND_ARGS (0 - all callbacks takes void,\
		1 - all callbacks take void *,2 - callbacks take any number of args)"
#define ALLOW_SEND_ARGS 1
#endif

#ifndef CALL_BACK_TYPE
//#warning "auto define of CALL_BACK_TYP (0 - only function, \
			1 - function or class, \
			2 - function, class, lambda)"
#define CALL_BACK_TYPE 1
#endif



namespace aos{

void default_sleep_function(sleep_block * sb){}
void default_error_function(){}

struct event_loop{
	char pipe_data[PIPE_SIZE];
	pipe<typename min_required_size_type<PIPE_SIZE>::type,__guard> _callback_queue;

	bool running;

	void (*sleep_function)(sleep_block * sb);
	void (*error_function)();
	sleep_block sb;
	
	constexpr static uint8_t max_callback_size = MAX_CALLBACK_SIZE;
	void run(){
		if(running){
			return;
		}else{
			running = true;
		}
		char _tmp_callback[MAX_CALLBACK_SIZE];
		uint8_t _tmp_pkg_size;
		while(running){
			_callback_queue.lock();
			if(_callback_queue.read((char*)(&_tmp_pkg_size),1)){ //read size of package consisting of call_function, delegator_class,args
				_callback_queue.read(_tmp_callback,_tmp_pkg_size);
				_callback_queue.unlock();
				
				call_delayed_function(*reinterpret_cast<VDELEGATORFUNCTYPE*>(_tmp_callback), //vcall function pointer
					_tmp_callback+VFUNCTION_SIZE, //pointer to delegator class
					_tmp_callback+DELEGATOR_SIZE+VFUNCTION_SIZE //pointer to args
					
				 );
			}else{
				sleep_function(&sb);
				_callback_queue.unlock();
			}
		}
		error_function();
	}

	void terminate(){
		running = false;
	}
	inline static event_loop*instance(){
		static event_loop loop;
		return &loop;
	}
	inline static decltype(_callback_queue) & get_pipe(){
		return instance()->_callback_queue;
	}
	friend class Application;
	private:

	event_loop():_callback_queue(pipe_data,PIPE_SIZE),
		sleep_function(default_sleep_function),
		error_function(default_error_function)
	{
		running = false;
	}

};

};


#endif /* EVENT_LOOP_H_ */