#ifndef DELEGATOR_H
#define  DELEGATOR_H

#include "type_traits.h"
namespace aos{
	
namespace __detail__{
template <typename...Args>
struct __DefaultClass__{
	void __DefaultFunction__(Args...){}
};

struct __VCallDefaultClass__{
	void __DefaultFunction__(char *){}
};

template <size_t N,typename arg_seq>
struct arg_getter;

template <size_t N,typename Arg0,typename...Args>
struct arg_getter<N,arg_sequence<Arg0,Args...>>{
	static constexpr inline __attribute__((always_inline)) auto get(char * args){
		return arg_getter<N-1,arg_sequence<Args...>>::get(args + sizeof(Arg0));
	}
};
template <typename Arg0,typename...Args>
struct arg_getter<0,arg_sequence<Arg0,Args...>>{
	static constexpr inline __attribute__((always_inline)) auto get(char * args){
		return *reinterpret_cast<Arg0*>(args);
	}
};

template <class C,typename arg_seq,typename IndexSeq>
struct __caller__;

template <class C,typename arg_seq,size_t...I>
struct __caller__<C,arg_seq,index_sequence<I...>>{
	static constexpr inline __attribute__((always_inline)) auto call(const C & c,char * args){
		c.call(arg_getter<I,arg_seq>::get(args)...);
	}
};



};

template <typename...Args>
struct ClassDelegator {
	typedef arg_sequence<Args...> AS;
	
	__detail__::__DefaultClass__<Args...> * __Object;
	void (__detail__::__DefaultClass__<Args...>::*__Slot)(Args...);
	
	
	constexpr ClassDelegator():__Object(0),__Slot(&__detail__::__DefaultClass__<Args...>::__DefaultFunction__){}
	
	template <typename T>
	ClassDelegator(T * Object, void (T::*Slot)(Args...)):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(Slot)){}
		
	template <typename T,typename = decltype(declval<T&>()(declval<Args>()...))>
	ClassDelegator(T * Object):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(&T::operator())){}
	
	void call(Args...args)const{
		(__Object->*__Slot)(args...);
	}
	
	void vcall(char * args)const{
		return __detail__::__caller__<ClassDelegator,AS,typename make_index_sequence<0,Args...>::type>::call(*this,args);
	}

	inline bool operator == (const ClassDelegator & other){
		return (__Object == other.__Object && __Slot==other.__Slot);
	}
	inline bool operator != (const ClassDelegator & other){
		return (__Object != other.__Object || __Slot!=other.__Slot);
	} 
};
template <typename...Args>
struct FunctionDelegator {
	typedef arg_sequence<Args...> AS;
	void (*__Slot)(Args...);
	
	constexpr FunctionDelegator():__Slot(0){}
	
	FunctionDelegator(decltype(__Slot) Slot):__Slot(Slot){}
		
	void call(Args...args)const{
		__Slot(args...);
	}
	
	void vcall(char * args)const{
		return __detail__::__caller__<FunctionDelegator,AS,typename make_index_sequence<0,Args...>::type>::call(*this,args);
	}
	inline bool operator == (const FunctionDelegator & other){
		return (__Slot==other.__Slot);
	}
	inline bool operator != (const FunctionDelegator & other){
		return (__Slot!=other.__Slot);
	} 
};

template <typename...Args>
struct ClassOrFunctionDelegator {
	typedef arg_sequence<Args...> AS;
	__detail__::__DefaultClass__<Args...> * __Object;
	void (__detail__::__DefaultClass__<Args...>::*__Slot)(Args...);
	
	constexpr ClassOrFunctionDelegator():__Object(0),__Slot(0){}
	inline ClassOrFunctionDelegator(const FunctionDelegator<Args...> & FD):ClassOrFunctionDelegator(FD.__Slot){}
	inline ClassOrFunctionDelegator(const ClassDelegator<Args...> & CD):ClassOrFunctionDelegator(CD.__Object,CD.__Slot){}	
	
	template <typename T>
	inline ClassOrFunctionDelegator (T * Object, void (T::*Slot)(Args...)):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(Slot)){}
	
	inline ClassOrFunctionDelegator(void (*F)(Args...)):__Object(reinterpret_cast<decltype(__Object)> (0)),
	__Slot(&__detail__::__DefaultClass__<Args...>::__DefaultFunction__){
		auto p =  reinterpret_cast<decltype(F)*>( (__detail__::__DefaultClass__<Args...>**)(this) + 1);
		*p = F;
	}

	template <typename T,typename = decltype(declval<T&>()(declval<Args>()...))>
	inline ClassOrFunctionDelegator (T * Object):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(&T::operator())){}
	
	
	void call(Args...args)const{
		if(__Object){
			//std::cout << "try to call Object" <<std::endl;
			(__Object->*__Slot)(args...);
		}
		else{
			//std::cout << "try to call f" <<std::endl;
			reinterpret_cast<void(*)(Args...)>( *((__detail__::__DefaultClass__<Args...>**)(this) + 1) ) (args...);
		}

	}
	
	
	void vcall(char * args)const{
		return __detail__::__caller__<ClassOrFunctionDelegator,AS,typename make_index_sequence<0,Args...>::type>::call(*this,args);
	}

	inline bool operator == (const ClassOrFunctionDelegator & other){
		return (__Object == other.__Object && __Slot==other.__Slot);
	}
	inline bool operator != (const ClassOrFunctionDelegator & other){
		return (__Object != other.__Object || __Slot!=other.__Slot);
	} 
};
/*
template <size_t max_size,typename...Args>
struct CommonDelegator{
	uint8_t method;
	char data[max_size];
	
	typedef void (*FuncType)(Args...);
	typedef __detail__::__DefaultClass__<Args...> * CPType;
	typedef __detail__::__DefaultClass__<Args...>  ClType;
	typedef void (__detail__::__DefaultClass__<Args...>::*CFType)(Args...);
	
	
	inline uint8_t size(){
		switch (method)
		{
		case 0:
			return sizeof(FuncType);
			break;
		case 1:
			return sizeof(CPType)+sizeof(CFType);
			break;
		default:
			return method;
			break;
		}
	}
	
	CommonDelegator()
	CommonDelegator(void (*Func)(Args...)):method(0){
		static_assert(max_size < sizeof(Func),"too few space for creating delegator object");
		reinterpret_cast<decltype(Func)>(data) = Func;
	}
	
	template <typename T>
	CommonDelegator(T * Object,void (T::*Slot)(Args...)):method(1){
		static_assert(max_size < sizeof(Object) + sizeof(Slot) ,"too few space for creating delegator object");
		reinterpret_cast<T * >(data) = Object;
		reinterpret_cast<decltype(Slot)>(data + sizeof(Object)) = Slot;
	}
	template <typename T>
	CommonDelegator(T * Object):method(1){
		typedef decltype(&T::operator()) Ftype;
		static_assert(max_size < sizeof(Object) + sizeof(Ftype) ,"too few space for creating delegator object");
		reinterpret_cast<T * >(data) = Object;
		reinterpret_cast<Ftype>(data + sizeof(Object)) = &T::operator();
	}
	
	template <typename LambdaType>
	CommonDelegator(LambdaType && Lambda):method(sizeof(CFType) + sizeof(typename rm_ref<LambdaType>::type)){
		static_assert(max_size < sizeof(typename rm_ref<LambdaType>::type) ,"too few space for creating delegator object");
		reinterpret_cast<CFType>(data) = &LambdaType::operator();
		*reinterpret_cast<typename rm_ref<LambdaType>::type*>(data+sizeof(CFType)) = Lambda;
	}
	
	void call(Args...args){
		switch (method)
		{
			case CLASS:
				((*reinterpret_cast<CPType*>(data))->*(*reinterpret_cast<CFType*>(data+sizeof(CPType))))(args...);
				break;
			case LAMBDA:
				(reinterpret_cast<ClType *>(data+sizeof(CFType) ) )->*(*reinterpret_cast<CFType*>(data))(args...);
				break;
			default:
				*reinterpret_cast<FuncType*>(data)(args...);
				break;
		}
	}
	
	template <typename IS>
	inline __attribute__((always_inline)) __vcall__helper__(void * args);
	template <size_t ...I>
	inline __attribute__((always_inline)) __vcall__helper__<__detail__::index_sequence<I...>>(void * args){
		call(__detail__::get_arg<I,Args...>(args)...);
	}
	
	void vcall(void * args){
		return __vcall__helper__<typename make_index_sequence<Args...>::type>(args);
	}
};
*/

#define DELEGATOR_SIZE sizeof(ClassOrFunctionDelegator<>)
#define VFUNCTION_SIZE sizeof(void (__detail__::__VCallDefaultClass__::*)(char *))
typedef  void (__detail__::__VCallDefaultClass__::*VDELEGATORFUNCTYPE)(char *);

/*
void call_delayed_function(char* Func,char * data,char * args){
	reinterpret_cast<__detail__::__VCallDefaultClass__*>(data)->*(reinterpret_cast<VDELEGATORFUNCTYPE*>(Func))(args);
}*/
void call_delayed_function(VDELEGATORFUNCTYPE Func,char * data,char * args){
	((reinterpret_cast<__detail__::__VCallDefaultClass__*>(data))->*Func)(args);
}




};
#endif