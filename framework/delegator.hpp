#ifndef DELEGATOR_H
#define  DELEGATOR_H

template <typename...Args>
class AbstractDelegator{
	
	public:
	virtual void call(Args... args)const = 0;
	virtual uint8_t size() const= 0;
	virtual ~AbstractDelegator(){}
	bool isSame(const AbstractDelegator *other) const{
		uint8_t this_size = this->size();
		if(this_size == other->size){
			uint8_t * F1 = reinterpret_cast<uint8_t *>(this);
			uint8_t * F2 = reinterpret_cast<uint8_t *>(other);
			for(uint8_t i =0;i<this_size;++i){
				if(F1[i] !=F2[i] )
					return false;
			}
			return true;
		}
		else
			return false;
	}
	
};

template <typename T,typename... Args>
class ClassSlot:public AbstractDelegator<Args...>{
	public:
	typedef void (T::*TFunction)(Args...args);
	
	private:
	T * Reciever;
	TFunction Func;
	
	
	
	public:
	ClassSlot(T * Reciever,TFunction Func):Reciever(Reciever),Func(Func){}
	~ClassSlot(){}
	void call(Args... args)const{
		return (Reciever->*Func)(args...);
	}
	
	uint8_t size()const{return sizeof(ClassSlot);}
	
	
};

template <typename FuncType,typename... Args>
class FunctionSlot:public AbstractDelegator<Args...>{
	FuncType Func;
	public:
	
	FunctionSlot(FuncType Func):Func(Func){}
	~FunctionSlot(){}
	void call(Args... args)const{
		return Func(args...);
	}
	uint8_t size()const{return sizeof(FunctionSlot);}
};

/*
template <class list_class, class...Args>
struct MultipleDelegator:AbstractDelegator<Args...>{
	list_class list_of_delegators;
	void call(Args...args){
		for(auto it = list_class.begin(); it != list_class.end();++it){
			(*it).call(args...);
		}
	}
};
*/

template <typename... Args>
struct DelegatorConstructor{
	template <typename T>
	static AbstractDelegator<Args...> * Construct(T * Reciever, typename ClassSlot<T,Args...>::TFunction Func){
		return new ClassSlot<T,Args...>(Reciever,Func);
	}

	template <typename Functype>
	static AbstractDelegator<Args...> * Construct(Functype Func){
		return new FunctionSlot<Functype,Args...>(Func);
	}
};

template <typename...Args>
struct __DefaultClass__{
	void __defaultFunction__(Args...){}
};

template <typename...Args>
struct AnyClassDelegator {
	
	__DefaultClass__<Args...> * __Object;
	void (__DefaultClass__<Args...>::*__Slot)(Args...);
	
	
	AnyClassDelegator():__Object(0),__Slot(&__DefaultClass__<Args...>::__defaultFunction__){}
	
	template <typename T>
	AnyClassDelegator(T * Object, void (T::*Slot)(Args...)):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(Slot)){}
		
	template <typename T>
	AnyClassDelegator(T * Object):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(&T::operator())){}
	
	void call(Args...args){
		(__Object->*__Slot)(args...);
	}
};

template <typename...Args>
struct AnyDelegator {
	
	__DefaultClass__<Args...> * __Object;
	void (__DefaultClass__<Args...>::*__Slot)(Args...);
	
	template <typename T>
	AnyDelegator (T * Object, void (T::*Slot)(Args...)):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(Slot)){}
	
	template <typename T>
	AnyDelegator (T * Object):
	__Object(reinterpret_cast<decltype(__Object)> (Object)),
	__Slot(reinterpret_cast<decltype(__Slot)>(&T::operator())){}
	
	AnyDelegator(void (*F)(Args...)):__Object(reinterpret_cast<decltype(__Object)> (0)),
									__Slot(&__DefaultClass__<Args...>::__defaultFunction__){
		auto p =  reinterpret_cast<void**>( (__DefaultClass__<Args...>**)(this) + 1);
		*p = reinterpret_cast<void *> (F);
	}
	void call(Args...args){
		if(__Object){
			//std::cout << "try to call Object" <<std::endl;
			(__Object->*__Slot)(args...);
		}
		else{
			//std::cout << "try to call f" <<std::endl;
			reinterpret_cast<void(*)(Args...)>( *((__DefaultClass__<Args...>**)(this) + 1) ) (args...);
		}

	}
};

template <typename...Args>
struct AbstractDelegatorWrapper{
	private:
	AbstractDelegator<Args...> * __D;
	public:
	inline void call(Args...args){
		__D->call(args...);
	}	
	inline bool operator == (const AbstractDelegatorWrapper & Other){
		return __D->isSame(&Other);
	}
	inline bool operator != (const AbstractDelegatorWrapper & Other){
		return !__D->isSame(&Other);
	}
	
	AbstractDelegatorWrapper(const AbstractDelegatorWrapper& Other){
		auto _size = Other.__D->size();
		__D = new uint8_t[_size];
		for(uint8_t i = 0;i<_size;++i){
			reinterpret_cast<uint8_t*>(__D)[i] = reinterpret_cast<uint8_t*>(Other.__D)[i];
		}
	}
	AbstractDelegatorWrapper(AbstractDelegatorWrapper && Other):__D(Other.__D){
		Other->__D = 0;
	}
	~AbstractDelegatorWrapper(){
		delete __D;
	}
	
	template <typename...DelegatorInfo>
	AbstractDelegatorWrapper(DelegatorInfo...info):
		__D(DelegatorConstructor<Args...>::Construct(info...)){}
};
#endif