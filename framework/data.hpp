#ifndef DATA_HPP
#define DATA_HPP

#include "global.hpp"
#define QSIZE 100

template <typename T,uint8_t _size = QSIZE>
struct static_queue{
	T buff[_size];
	uint8_t start;
	uint8_t len;
	
	static_queue():start(0),len(0){}
	
	inline uint8_t size(){
		return _size;
	}
	uint8_t is_empty(){
		return !len;
	}
	uint8_t is_full(){
		return len < _size;
	}
	T pop(){
		len --;
		return buff[start++];
		
	}
	void push(T value){
		uint8_t last = (start + (uint16_t)len)%_size;
		if(len == 0 || last != start){
			len ++;
			buff[last] = value;
		}
	}
};

template <typename T>
struct dynamic_queue{
	T *buff;
	uint8_t _size;
	uint8_t start;
	uint8_t len;
	
	dynamic_queue():_size(0),start(0),len(0),buff(0){}
	dynamic_queue(uint8_t _size):_size(_size),start(0),len(0),buff(new T[_size]){}
	~dynamic_queue(){
		if(_size){
			delete [] buff;
		}
	}
	
	void resize(uint8_t new_size){
		T * new_buff = new T[new_size];
		for(uint8_t i = 0; i< len && i < new_size;++i){
			new_buff[i] = buff[ (start + (uint16_t)i)%_size];
		}
		if(_size){
			delete [] buff;
		}
		buff = new_buff;
	}
	
	inline uint8_t size(){
		return _size;
	}
	uint8_t is_empty(){
		return !len;
	}
	uint8_t is_full(){
		return len < _size;
	}
	T pop(){
		len --;
		return buff[start++];
		
	}
	void push(T value){
		uint8_t last = (start + (uint16_t)len)%_size;
		if(len == 0 || last != start){
			len ++;
			buff[last] = value;
		}
		else if (last == start){
			uint8_t newsize = 255;
			if(_size < 128)
				newsize = _size*2;
			resize(newsize);
		}
	}
};


template <typename T,uint8_t _size = 100>
struct static_list{
	struct list_info{
		uint8_t next;
		T value;
		list_info(uint8_t next,T value):next(next),value(value){}
		list_info():next(0){}
	};
	// if _data[i].next == _size - the end of list
	// if _data[i].next == i - uninitialized
	// two deprecated value of indexing,
	// because _data have size _size and a.next couldn't refer to a
	
	list_info _data[_size];
	uint8_t first_value;
	
	static_list():first_value(_size){
		for(uint8_t i=1;i<_size;++i){
			_data[i].next = i;
		}
	}
	uint8_t size()const{return size;}
	uint8_t fullness() const{
		uint8_t i = first_value;
		uint8_t len = 0;
		for(;i != _size;i = _data[i].next){
			len ++;
		}
		return len;
	}
	

	bool push_back(T val){
		uint8_t inew = 0;
		for(;inew != _size;++inew){
			if(_data[inew].next == inew){
				break;
			}
		}
		if(inew == _size)
		return false;

		uint8_t i = first_value;
		for(; _data[i].next != _size;i = _data[i].next);
		
		_data[i].next = inew;
		_data[inew].next = _size;
		_data[inew].value = val;
		return true;
	}
	bool push_front(T val){
		uint8_t inew = 0;
		for(;inew != _size;++inew){
			if(_data[inew].next == inew){
				break;
			}
		}
		if(inew == _size)
		return false;

		_data[inew].value = val;
		_data[inew].next= first_value;
		first_value = inew;
		return true;
	}
	
	struct iterator{
		uint8_t i;
		uint8_t prev;
		list_info * _data;
		
		iterator(list_info * _data,uint8_t i):_data(_data),i(i),prev(_size){}
		
		iterator & operator ++(){
			prev = i;
			i = _data[i].next;
			return *this;
		}
		
		T & operator *(){
			return _data[i].value;
		}
		bool operator ==(const iterator & it) const{
			return i == it.i && _data == it._data;
		}
		bool operator !=(const iterator & it) const{
			return i != it.i || _data != it._data;
		}
	};
	
	inline iterator end(){
		return iterator(_data,_size);
	}
	inline iterator begin(){
		return iterator(_data,first_value);
	}
	
	iterator & remove(iterator & it){
		if(it.prev == _size){
			if(first_value == it.i){
				first_value = _data[first_value].next;
				_data[it.i].next = it.i;
				it.i = first_value;
			}
		}
		else{
			_data[it.prev].next = _data[it.i].next;
			uint8_t itmp = it.i;
			it.i = _data[it.i].next;
			_data[itmp].next = itmp;
		}
		return it;
	}
	uint8_t remove(const T & val){
		uint8_t rm_cnt = 0;
		for(auto it = begin();it!= end(); ){
			if(*it == val){
				remove(it);
				rm_cnt++;
			}
			else{
				++it;
			}
			return rm_cnt;
		}
	}
	
};


template <typename T>
struct list_data{
	T data;
	struct list_data * next;
	list_data(T data,list_data * next = 0):data(data),next(next){}
};

template <typename T>
class list{
	list_data<T> *first;
	
	public:
	list():first(0){}
	
	void push_back(T val){
		if(first){
			auto it = first;
			for(;it->next != 0; it = it->next);
			it->next = new list_data<T>(val);
		}
		else{
			first = new list_data<T>(val);
		}
		
	}
	void push_front(T val){
		first = new list_data<T>(val,first);
	}
	
	struct iterator{
		list_data<T> *ptr;
		list_data<T> *prev;
		
		iterator(list_data<T> *ptr):ptr(ptr),prev(0){}
		iterator & operator ++(){
			prev = ptr;
			ptr = ptr->next;
			return *this;
		}
		bool operator ==(const iterator & it) const{
			return ptr == it.ptr;
		}
		bool operator !=(const iterator & it) const{
			return ptr != it.ptr;
		}
		T & operator *(){
			return ptr->data;
		}
	};
	
	iterator begin(){
		return iterator(first);
	}
	iterator end(){
		return iterator(0);
	}
	
	iterator & remove(iterator & it){
		if(it.ptr){
			if(it.prev){
				auto tmp_ptr = it.ptr->next;
				it.prev->next = tmp_ptr;
				delete it.ptr;
				it.ptr = tmp_ptr;
			}
			else{
				first = it.ptr->next;
				delete it.ptr;
				it.ptr =  first;
			}
		}
		return it;
	}
	
	uint8_t remove(T val){
		uint8_t rm_cnt = 0;
		for(auto it = begin(); it != end();){
			if(*it == val){
				remove(it);
				rm_cnt ++;
			}
			else
			++it;
		}
		return rm_cnt;
	}
	
	template <typename FuncType>
	uint8_t remove_if(FuncType Condtion){
		uint8_t rm_cnt = 0;
		for(auto it = begin(); it != end();){
			if(Condtion(*it)){
				remove(it);
				rm_cnt ++;
			}
			else
			++it;
		}
		return rm_cnt;
	}
};



#endif