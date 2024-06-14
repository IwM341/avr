/*
 * pipe.h
 *
 * Created: 08.04.2023 16:37:07
 *  Author: MainUser
 */ 


#ifndef PIPE_H_
#define PIPE_H_
#include <ctype.h>
namespace asyncruino{

template <typename T>
struct alignas(alignof(T)) T_container{
	constexpr static size_t size = sizeof(T);
	char data[size];
	inline operator T &(){
		return *reinterpret_cast<T*>(data);
	}
	inline operator const T &()const{
		return *reinterpret_cast<T*>(data);
	}
	inline void * ptr(){
		return data;
	}
};


/**
*	\brief queue type with static size
*	\tparam T value type of queue
*	\tparam size_type indexing type, size_t or uint8_t
*/	
template <typename T,typename size_type,size_type reserved_size>
struct pipe{
	constexpr static size_type reserved = reserved_size;
	typedef T value_type;

	T _data[reserved_size];
	size_type _start;
	size_type _size;
	public:
	inline pipe():
		_start(0),_size(0){
			//static_assert(is_deg_2<reserved_size>::value,"pipe size should be degree of 2");
		}
	
	/**
	\return if the queue is empty
	*/
	inline  bool empty()const {return !_size;}
	/**
	\return if the queue is not empty
	*/
	inline  bool not_empty()const{return _size;}
	/**
	\return temporary queue length
	*/
	inline  size_type size()const{return _size;}

	inline T & front() {return _data[_start];}
	inline const T & front() const{return _data[_start];}
	
	/**
	\return temporary queue remain size
	*/
	inline  size_type remain_space()const{return reserved-_size;}
	/**
		\brief write bytes using guard
		\param [in] data source 
		\param [in] len number of bytes to write
		\return if write succeed
	*/
	/**
		\brief write bytes without using guard
		\param [in] data source 
		\param [in] len number of bytes to write
		\return if write succeed
	*/
	inline bool write(const T & value){
		if(_size == reserved){
			return false;
		}
		T * m_ptr = _data + (_start+_size)%reserved;
		*m_ptr = value;
		_size++;
		return true;
	}
	inline bool read(T & value){
		if(_size){
			value = _data[_start];
			_start++;
			if(_start >= reserved){
				_start = 0;
			}
			_size--;
			return true;
		}
		return false;
	}
	inline bool write(const T * data,size_type len){
		if(remain_space() < len){
			return false;
		}
		size_type m_index = (_start+_size);
		_size += len;
		if(m_index < reserved){
			T * ptr = _data + m_index;
			if(m_index + len <= reserved){
				while(len){
					*ptr = *data;
					++ptr;
					++data;
					--len;
				}
			}
			else{
				size_type first_part_size = reserved-m_index;
				len -= first_part_size;
				while(first_part_size){
					*ptr = *data;
					++ptr;
					++data;
					--first_part_size;
				}
				ptr = _data;
				while(len){
					*ptr = *data;
					ptr++;
					data++;
					len--; 
				}
			}
		}
		else{
			m_index -= reserved;
			T * ptr = _data + m_index;

			while(len){
				*ptr = *data;
				++ptr;
				++data;
				--len;
			}
			
		}
		return true;
	}
	
	/**
		\brief read bytes without using guard
		\param [out] data destination 
		\param [in] len number of bytes to write
		\return number of read items
	*/
	size_type read(T * data,size_type len){
		size_type n_bytes = (_size > len ? len : _size);
		_size -= n_bytes;
		size_type bytes_before_end = reserved - _start;
		size_type bytes_1 = (bytes_before_end > n_bytes ? n_bytes : bytes_before_end);
		size_type bytes_2 = n_bytes-bytes_1;
		T * ptr = _data + _start;
		_start = (_start + n_bytes)%reserved; 
		while(bytes_1){
			*data = *ptr;
			++ptr;
			++data;
			bytes_1--;
		}
		if(bytes_2){
			ptr = _data;
			while(bytes_2){
				*data = *ptr;
				++ptr;
				++data;
				bytes_2--;
			}
		}
		return n_bytes;
	}
};

};


#endif /* PIPE_H_ */