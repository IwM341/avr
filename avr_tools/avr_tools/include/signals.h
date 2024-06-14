/*
 * signals.h
 *
 * Created: 09.04.2023 17:02:28
 *  Author: MainUser
 */ 


#ifndef SIGNALS_H_
#define SIGNALS_H_

#ifndef DEFAULT_MAX_SLOT_COUNT
//#warning "auto define of DEFAULT_MAX_SLOT_COUNT"
#define DEFAULT_MAX_SLOT_COUNT 4
#endif

#ifndef DEFAULT_MAX_SOFT_SLOT_COUNT
//#warning "auto define of DEFAULT_MAX_SLOT_COUNT"
#define DEFAULT_MAX_SOFT_SLOT_COUNT 6
#endif

#ifndef MAX_CALLBACK_SIZE
//#warning "auto define of MAX_CALLBACK_SIZE"
#define MAX_CALLBACK_SIZE 24
#endif


#include "set.h"
#include "delegator.h"
#include "event_loop.h"

#define emit
namespace aos{
template <uint8_t max_slots,typename DelegatorClass,typename...Args>
struct direct_signal_impl{
	DelegatorClass _slots_array[max_slots];
	set<DelegatorClass,uint8_t,__guard> _slots;
	
	direct_signal_impl():_slots(_slots_array,max_slots){}
		
		
	template <typename...Args1>
	inline bool connect(Args1&&...args){
		return _slots.sinsert(args...);
	}
	template <typename...Args1>
	inline void disconnect(Args1&&...args){
		_slots.sremove_compare(DelegatorClass(args...));
	}
	
	inline void operator()(Args...args){
		_slots.lock();
		for(uint8_t i=0;i != _slots._size;++i){
			_slots_array[i].call(args...);
		}
		_slots.unlock();
	}
};

template <typename...Args>
using direct_c_signal = direct_signal_impl<DEFAULT_MAX_SLOT_COUNT,ClassDelegator<Args...>,Args...>;

template <typename...Args>
using direct_signal = direct_signal_impl<DEFAULT_MAX_SLOT_COUNT,ClassDelegator<Args...>,Args...>;

template <typename...Args>
using direct_f_signal =direct_signal_impl<DEFAULT_MAX_SLOT_COUNT,FunctionDelegator<Args...>,Args...>;

template <typename...Args>
using direct_cf_signal = direct_signal_impl<DEFAULT_MAX_SLOT_COUNT,ClassOrFunctionDelegator<Args...>,Args...>;


template <typename FuncType,size_t max_slots>
struct direct_signal_impl_c;

template <typename...Args,size_t max_slots>
struct direct_signal_impl_c<void(Args...),max_slots>{
	typedef direct_signal_impl<max_slots,ClassDelegator<Args...>,Args...> type;
};

template <typename FuncType,size_t max_slots=DEFAULT_MAX_SLOT_COUNT>
using dc_signal = typename direct_signal_impl_c<FuncType,max_slots>::type;


template <typename FuncType,size_t max_slots>
struct direct_signal_impl_f;

template <typename...Args,size_t max_slots>
struct direct_signal_impl_f<void(Args...),max_slots>{
	typedef direct_signal_impl<max_slots,FunctionDelegator<Args...>,Args...> type;
};

template <typename FuncType,size_t max_slots=DEFAULT_MAX_SLOT_COUNT>
using df_signal = typename direct_signal_impl_c<FuncType,max_slots>::type;

template <typename FuncType,size_t max_slots>
struct direct_signal_impl_cf;

template <typename...Args,size_t max_slots>
struct direct_signal_impl_cf<void(Args...),max_slots>{
	typedef direct_signal_impl<max_slots,ClassOrFunctionDelegator<Args...>,Args...> type;
};

template <typename FuncType,size_t max_slots=DEFAULT_MAX_SLOT_COUNT>
using dcf_signal = typename direct_signal_impl_c<FuncType,max_slots>::type;

template <typename FuncType,size_t max_slots=DEFAULT_MAX_SLOT_COUNT>
using dc_signal = dcf_signal<FuncType,max_slots>;


template <uint8_t max_slots,typename...Args>
using direct_c_signal_cs = direct_signal_impl<max_slots,ClassDelegator<Args...>,Args...>;

template <uint8_t max_slots,typename...Args>
using direct_signal_cs = direct_signal_impl<max_slots,ClassDelegator<Args...>,Args...>;

template <uint8_t max_slots,typename...Args>
using direct_f_signal_cs =direct_signal_impl<max_slots,FunctionDelegator<Args...>,Args...>;

template <uint8_t max_slots,typename...Args>
using direct_cf_signal_cs = direct_signal_impl<max_slots,ClassOrFunctionDelegator<Args...>,Args...>;


template <typename Signal,typename...Args>
inline bool connect(Signal * S,Args...args){
	return S->connect(args...);
};

template <typename Signal,typename...Args>
inline void disconnect(Signal * S,Args...args){
	S->disconnect(args...);
};

namespace __detail__{
	template <typename Writer>
	inline void __write(Writer && w){}

	template <typename Writer,typename Arg0,typename...Args>
	inline void __write(Writer && w,Arg0 arg0,Args...args){
		w.write((char*)&arg0,sizeof(Arg0));
		__write(w,args...);
	}
	template <typename Delegator,typename pipetype,typename...Args>
	inline void send_delegator(Delegator const & D,pipetype & p,Args...args){
		static const uint8_t clbk_size = args_size<Args...>::value + DELEGATOR_SIZE+VFUNCTION_SIZE;
		if(p.remain_space()> clbk_size+1){
			p.write((char *)&clbk_size,1);
			auto vfunc = (&ClassOrFunctionDelegator<Args...>::vcall);
			p.write((char*)&vfunc,VFUNCTION_SIZE);
			p.write((char*)(&D),DELEGATOR_SIZE);
			__write(p,args...);
		}
	}
};


template <uint8_t max_slots,class DelegatorClass,typename...Args>
	struct soft_signal_impl{
	DelegatorClass _slots_array[max_slots];
	set<DelegatorClass,uint8_t,__guard> _slots;
	constexpr static uint8_t clbk_size = args_size<Args...>::value + DELEGATOR_SIZE+VFUNCTION_SIZE;


	soft_signal_impl():_slots(_slots_array,max_slots){}


	template <typename...Args1>
	inline bool connect(Args1&&...args){
		return _slots.sinsert(args...);
	}
	template <typename...Args1>
	inline void disconnect(Args1&&...args){
		_slots.sremove_compare(DelegatorClass(args...));
	}

	inline void operator()(Args...args){
		auto & pipe = event_loop::get_pipe();
		_slots.lock();
		pipe.lock();
		
		//static_assert(clbk_size <= MAX_CALLBACK_SIZE,
			//"too many arguments in callback, try reduce or increase MAX_CALLBACK_SIZE define");
		uint8_t m_clbk_size = clbk_size;
		for(uint8_t i=0;i != _slots._size && pipe.remain_space() > m_clbk_size+1;++i){
			pipe.write((char *)&m_clbk_size,1);
			auto vfunc = (&ClassOrFunctionDelegator<Args...>::vcall);
			pipe.write((char*)&vfunc,VFUNCTION_SIZE);
			pipe.write((char*)(_slots_array + i),DELEGATOR_SIZE);
			__detail__::__write(pipe,args...);
		}
		pipe.unlock();
		_slots.unlock();
	}
};

template <typename...Args>
using signal = soft_signal_impl<DEFAULT_MAX_SOFT_SLOT_COUNT,ClassOrFunctionDelegator<Args...>,Args...>;

template <uint8_t max_slots,typename...Args>
using signal_cs = soft_signal_impl<max_slots,ClassOrFunctionDelegator<Args...>,Args...>;

};

#endif /* SIGNALS_H_ */