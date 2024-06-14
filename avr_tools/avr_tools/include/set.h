/*
 * set.h
 *
 * Created: 09.04.2023 9:05:19
 *  Author: MainUser
 */ 


#ifndef SET_H_
#define SET_H_

#include "guard.h"


namespace aos{
	template <typename T,typename size_type,typename guard_type>
	struct set{
		T * _data;
		size_type _reserved;
		size_type _size;
		guard_type guard;
		
		public:
		set(T * _data,size_type _reserved):_data(_data),_reserved(_reserved),_size(_size){}
		inline __attribute__((always_inline)) T * begin(){return _data;}
		inline __attribute__((always_inline)) T * end(){return _data+_size;}
		inline __attribute__((always_inline)) const T * cbegin()const{return _data;}
		inline __attribute__((always_inline)) const T * cend()const{return _data+_size;}
		inline __attribute__((always_inline)) const T * begin()const{return _data;}
		inline __attribute__((always_inline)) const T * end()const{return _data+_size;}
		
		inline __attribute__((always_inline)) void lock(){guard.lock();}
		inline __attribute__((always_inline)) void unlock(){guard.unlock();}
		
		template <typename...Args>
		inline bool insert(Args &&...args){
			if(_size < _reserved){
				new (_data+_size++) T(static_cast<Args&&>(args)...);
				return true;
			}
			else{
				return false;
			}
		}
		template <typename...Args>
		inline __attribute__((always_inline)) bool sinsert(Args &&... args){
			lock_guard<guard_type> lg(guard);
			return insert(static_cast<Args&&>(args)...);
		}
		
		inline void remove(T * position){
			if(position  < _data  + _size)
			position->~T();
			_size--;
			if(_size)
				position = (_data + _size - 1);
		}
		inline __attribute__((always_inline)) bool sremove(T * position){
			lock_guard<guard_type>lg (guard) ;
			return remove(position);
		}
		inline void remove_compare(T const& value){
			T * ptr = begin();
			while(ptr != end()){
				if(*ptr == value){
					remove(ptr);
				}
				else{
					++ptr;
				}
			}
		}
		inline __attribute__((always_inline)) void sremove_compare(T const& value){
			lock_guard<guard_type> lg(guard);
			return remove_compare(value);
		}
		
		template <typename CondType>
		inline void remove_if(CondType && condition){
			T * ptr = begin();
			while(ptr != end()){
				if(condition(*ptr))
					remove(ptr);
				else
					++ptr;
			}
		}
		template <typename CondType>
		inline __attribute__((always_inline)) void sremove_if(CondType && condition){
			lock_guard<guard_type> lg(guard);
			remove_if(static_cast<CondType&&>(condition));
		}
		
	};
	
	/*
	template <typename T,typename size_type,typename guard_type>
	struct memory{
		struct mem_item{
			T data;
			size_type _prev;
			size_type _next;
		};
		mem_item * _buffer;
		
		size_type _first;
		size_type _size;
		size_type _reserved;
		guard_type guard;
		
		constexpr inline __attribute__((always_inline)) static size_type recommended_buffer_size(size_type m_size){
			return m_size*sizeof(mem_item);
		}
		template <size_type m_size>
		struct recommended_buff_size{
			constexpr static size_type value = m_size*sizeof(mem_item);
		};
			
		
		inline __attribute__((always_inline)) memory(void * _buffer,size_type _reserved):_buffer(_buffer),_reserved(_reserved),_size(0),_first(_reserved){}
			
		T * allocate(){
			if(_size < _reserved){
				if(_first > 0){ 
					_buffer->_next = _first;
					(_buffer+_first)->_prev = 0;
					_first = 0;
					++_size;
					return _buffer;
				}else{
					mem_item * ptr = _buffer;
					
				}
			}else{
				return nullptr;
			}
		}
	};
	*/
	
/*
	template <typename T,typename size_type,typename guard_type>
	struct list{
		struct list_data{
			T value;
			list_data *_next;
			list_data *_prev;
		};
		struct iterator{
			list_data * _data;
			
			inline __attribute__((always_inline)) iterator & operator++(){
				_data = _data->_next;
				return *this;
			}
			inline __attribute__((always_inline)) iterator & operator--(){
				_data = _data->_prev;
				return *this;
			}
			inline __attribute__((always_inline)) operator == (iterator const & it1)const{
				return it1._data == _data;
			}
			inline __attribute__((always_inline)) operator != (iterator const & it1)const{
				return it1._data != _data;
			}
			inline __attribute__((always_inline)) bool is_end()const{return _data == nullptr;}
			inline __attribute__((always_inline)) bool not_end()const{return _data;}
			inline __attribute__((always_inline)) operator const_iterator()const{return const_iterator{_data};}
			__attribute__((always_inline)) T & operator * (){return _data->value;}
			__attribute__((always_inline)) T * operator ->(){return &_data->value;}	
		};
		struct const_iterator{
			const list_data * _data;
			inline __attribute__((always_inline)) const_iterator & operator++(){
				_data = _data->_next;
				return *this;
			}
			inline __attribute__((always_inline)) const_iterator & operator--(){
				_data = _data->_prev;
				return *this;
			}
			inline __attribute__((always_inline)) operator == (const_iterator const & it1)const{
				return it1._data == _data;
			}
			inline __attribute__((always_inline)) operator != (const_iterator const & it1)const{
				return it1._data != _data;
			}
			inline __attribute__((always_inline)) bool is_end()const{return _data == nullptr;}
			inline __attribute__((always_inline)) bool not_end()const{return _data;}
			
			__attribute__((always_inline)) const T & operator * ()const{return _data->value;}
			__attribute__((always_inline)) const T * operator ->()const{return &_data->value;}
		};
		
		list_data *_data;
		list_data *_first;
		size_type _size;
		size_type _reserved;
		guard_type guard;
		
		template <size_type m_size>
		struct recommended_buff_size{
			constexpr static size_type value = m_size*sizeof(list_data);
		};
		
		
		list(void * _data,size_type _reserved):_data(_data),_reserved(_reserved),_first(nullptr),_size(0){}
		template <typename...Args>
		inline bool insert(iterator place,Args&&...args){
			if(_size < _reserved){
				list_data * ptr = _data+_size;
				new (&(ptr->value)) T(static_cast<Args&&>(args)...);
				ptr->_next = place._data;
				ptr->_prev = place->_prev;
				if(place.not_end()){
					place->_prev = ptr;
					if(place->_prev){
						place->_prev->_next = ptr;
					}
				}
				return true;
			}else{
				return false;
			}
		}
		inline __attribute__((always_inline)) bool sinsert(iterator place,Args&&...args){
			lock_guard<guard_type>(guard) lg;
			return insert(place,static_cast<Args&&>(args)...);
		}
		inline void remove(iterator &place){
			
		}
		
	};
	*/
};

#endif /* SET_H_ */