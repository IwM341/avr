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
			uint8_t * F1 = static_cast<uint8_t *>(this);
			uint8_t * F2 = static_cast<uint8_t *>(other);
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
	typedef void (*TFunction)(Args...args);
	
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
#endif