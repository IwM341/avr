/*
 * pipe.h
 *
 * Created: 08.04.2023 16:37:07
 *  Author: MainUser
 */ 


#ifndef PIPE_H_
#define PIPE_H_

#include "guard.h"

namespace aos{
	
/**
*	\brief class i/o for reading and writing bytes
*	
*	\tparam size_type  Type of buffer size: uint8_t if buffer length < 256 and short otherwise
*	\tparam guard_type  type to preserve pipe from race condition, should have functions lock() and unlock()
*/	
template <typename size_type,typename guard_type = no_guard>
struct pipe{
	char *_data;
	size_type _reserved;
	size_type _start;
	size_type _end;
	size_type _size;
	mutable guard_type guard;
	
	public:
	/**
	* \param [in] _data pointer to allocated bytes, where the pipe should go
	* \param [in] _reserved the size of memory in _data, which can be used by pipe
	* 
	* example of usage
		\code
		char mem[240];
		pipe<uint8_t>(mem,240);
		\endcode
	*/
	inline pipe(char *_data,size_type _reserved):
		_data(_data),_reserved(_reserved),_start(0),_end(0),_size(0){}
	
	/**
	\return if the queue is empty
	*/
	inline  bool empty()const {return _size;}
	/**
	\return if the queue is not empty
	*/
	inline  bool not_empty()const{return !_size;}
	/**
	\return temporary queue length
	*/
	inline  size_type size()const{return _size;}
	
	/**
	\return temporary queue remain size
	*/
	inline  size_type remain_space()const{return _reserved-_size;}
		
	/**
	lock internal guard
	*/
	inline  void lock()const{guard.lock();}
	/**
	unlock internal guard
	*/
	inline  void unlock()const{guard.unlock();}

	
	/**
		\brief write bytes using guard
		\param [in] data source 
		\param [in] len number of bytes to write
		\return if write succeed
	*/
	inline bool swrite(const char * data,size_type len){
		lock_guard<guard_type> lg(guard);
		return write(data,len);
	}
	/**
		\brief read bytes using guard
		\param [out] data destination 
		\param [in] len number of bytes to write
		\return if read succeed
	*/
	inline bool sread(char * data,size_type len){
		lock_guard<guard_type> lg(guard);
		return read(data,len);
	}
	
	/**
		\brief write bytes without using guard
		\param [in] data source 
		\param [in] len number of bytes to write
		\return if write succeed
	*/
	inline bool write(const char * data,size_type len){
		if(_reserved-_size < len){
			return false;
		}
		else if(_reserved-_end > len){
			char * ptr = _data + _end;
			_size+=len;
			_end+=len;
			while(len){
				*(ptr++) = *(data++);
				--len;
			}
		}
		else{
			char * ptr = _data + _end;
			_end = (len - (_reserved-_end));
			_size+=len;
			while(len > _end){
				*(ptr++) = *(data++);
				--len;
			}
			ptr = _data;
			while(len){
				*(ptr++) = *(data++);
				--len;
			}
		}
		return true;
	}
	
	/**
		\brief read bytes without using guard
		\param [out] data destination 
		\param [in] len number of bytes to write
		\return if read succeed
	*/
	bool read(char * data,size_type len){
		if(_size < len){
			return false;
		}
		else if(_reserved-_start > len){
			char * ptr = _data + _start;
			_size -= len;
			_start += len;
			while(len){
				*(data++) = *(ptr++);
				--len;
			}
		}
		else{
			char * ptr = _data + _start;
			_start = (len - (_reserved-_start));
			_size-=len;
			while(len > _start){
				*(data++) = *(ptr++);
				--len;
			}
			ptr = _data;
			while(len){
				*(data++) = *(ptr++);
				--len;
			}
		}
		return true;
	}
};

};


#endif /* PIPE_H_ */