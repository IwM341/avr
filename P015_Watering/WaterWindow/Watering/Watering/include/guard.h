#include "type_traits.h"
#include <avr/interrupt.h>
#include "../../FreeRTOS/semphr.h"

struct mutex{
	SemaphoreHandle_t xMutex;
	void lock(){
		xSemaphoreTake(xMutex, portMAX_DELAY);
	};
	void unlock(){
		xSemaphoreGive(xMutex);
	}
};

struct atomic_guard{
	uint8_t sreg;
	inline void lock(){
		uint8_t sreg_tmp = SREG;
		cli();
		sreg = sreg_tmp;
	}
	inline void unlock(){
		SREG = sreg;
	}
};

struct guard_timer0{
	mutex m;
	inline guard_timer0(){}
	
	inline void lock(){
		TIMSK0 = 0;
		m.lock();
	}
	inline void unlock(){
		m.unlock();
		TIMSK0 = 1<<TOIE0;
	}
};

template<typename Mutex_t>
struct lock_guard{
	Mutex_t & _m;
	lock_guard(Mutex_t & _m):_m(_m){
		_m.lock();
	}
	~lock_guard(){
		_m.unlock();
	}
};

template <typename T,typename guarg_t = mutex>
struct guarded{
	T value;
	mutable guarg_t m;
	
	template <typename...Args>
	inline guarded(Args &&...args):value(Std::forward<Args>(args)...){}

	inline void lock()const{
		m.lock();
	}
	inline void unlock()const{
		m.unlock();
	}
	
	
	
	
	template <typename Func_t,
		Std::enable_if_not_same_t<Std::invoke_result_t<Func_t,T &>,void,bool> = true>
	inline auto apply(Func_t && F){
		//static_assert(!Std::is_same_v<Std::invoke_result_t<Func_t,T &>,void>,"void function in not void spec");
		lock();
		auto result = F(value);
		unlock();
		return result;
	}
	
	template <typename Func_t,
		Std::enable_if_same_t<Std::invoke_result_t<Func_t,T &>,void,bool> = true>
	inline void apply(Func_t && F){
		//static_assert(Std::is_same_v<Std::invoke_result_t<Func_t,T &>,void>,"not void function in void spec");
		lock();
		F(value);
		unlock();
	}
	
	
	
	
	template <typename Func_t>
	inline auto get(Func_t && F) const{
		lock();
		auto m_value = F(value);
		unlock();
		return m_value;
	}
	
	inline Std::remove_reference_t<T> get() const{
		return get([](auto const &x){return x;});
	}
};