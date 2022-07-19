#ifndef TASK_H
#define TASK_H

class AbstractTask{
	public:
	virtual void call() = 0;
	virtual uint8_t  size()const = 0;
	virtual ~AbstractTask(){}
};

template<typename FuncType, typename...Args>
class FunctionTask;


template<typename FuncType>
class FunctionTask<FuncType>:public AbstractTask{
	FuncType F;
	
	public:
	FunctionTask(FuncType F):F(F){}
	void call(){F();}
	uint8_t size()const{return sizeof(*this);}
};

template<typename FuncType, typename TypeArg0>
class FunctionTask<FuncType,TypeArg0>:public  AbstractTask{
	FuncType F;
	TypeArg0 arg0;
	
	public:
	FunctionTask(FuncType F,TypeArg0 arg0):F(F),arg0(arg0){}
	void call(){F(arg0);}
	uint8_t  size()const{return sizeof(*this);}
};

template<typename FuncType, typename TypeArg0,typename TypeArg1>
class FunctionTask<FuncType,TypeArg0,TypeArg1>: public AbstractTask{
	FuncType F;
	TypeArg0 arg0;
	TypeArg1 arg1;
	
	public:
	FunctionTask(FuncType F,TypeArg0 arg0,TypeArg1 arg1):F(F),arg0(arg0),arg1(arg1){}
	void call(){F(arg0,arg1);}
	uint8_t  size()const{return sizeof(*this);}
};

template<typename FuncType, typename TypeArg0,typename TypeArg1,typename TypeArg2>
class FunctionTask<FuncType,TypeArg0,TypeArg1,TypeArg2>:public  AbstractTask{
	FuncType F;
	TypeArg0 arg0;
	TypeArg1 arg1;
	TypeArg2 arg2;
	
	public:
	FunctionTask(FuncType F,TypeArg0 arg0,TypeArg1 arg1,TypeArg2 arg2):F(F),arg0(arg0),arg1(arg1),arg2(arg2){}
	void call(){F(arg0,arg1,arg2);}
	uint8_t  size()const{return sizeof(*this);}
};



template<typename ClassType, typename...Args>
class ClassTask;


template<typename ClassType>
class ClassTask<ClassType>:public AbstractTask{
	
	public:
	typedef void (ClassType::*FuncType) (void);
	
	ClassTask(ClassType * Object,FuncType Slot):Object(Object),Slot(Slot){}
	void call(){(Object->*Slot)();}
	uint8_t size()const{return sizeof(*this);}
	
	private:
	ClassType *Object;
	FuncType Slot;
};


template<typename ClassType,typename TypeArg0>
class ClassTask<ClassType,TypeArg0>:public AbstractTask{
	
	public:
	typedef void (ClassType::*FuncType) (TypeArg0);
	
	ClassTask(ClassType * Object,FuncType Slot,TypeArg0 arg0):Object(Object),Slot(Slot),arg0(arg0){}
	void call(){(Object->*Slot)(arg0);}
	uint8_t size()const{return sizeof(*this);}
	
	private:
	ClassType *Object;
	FuncType Slot;
	TypeArg0 arg0;
};

template<typename ClassType,typename TypeArg0,typename TypeArg1>
class ClassTask<ClassType,TypeArg0,TypeArg1>:public AbstractTask{
	
	public:
	typedef void (ClassType::*FuncType) (TypeArg0,TypeArg1);
	
	ClassTask(ClassType * Object,FuncType Slot,TypeArg0 arg0,TypeArg1 arg1):Object(Object),Slot(Slot),arg0(arg0),arg1(arg1){}
	void call(){(Object->*Slot)(arg0,arg1);}
	uint8_t size()const{return sizeof(*this);}
	
	private:
	ClassType *Object;
	FuncType Slot;
	TypeArg0 arg0;
	TypeArg1 arg1;
};

template<typename ClassType,typename TypeArg0,typename TypeArg1,typename TypeArg2>
class ClassTask<ClassType,TypeArg0,TypeArg1,TypeArg2>:public AbstractTask{
	
	public:
	typedef void (ClassType::*FuncType) (TypeArg0,TypeArg1,TypeArg2);
	
	ClassTask(ClassType * Object,FuncType Slot,TypeArg0 arg0,TypeArg1 arg1,TypeArg2 arg2):Object(Object),Slot(Slot),arg0(arg0),arg1(arg1),arg2(arg2){}
	void call(){(Object->*Slot)(arg0,arg1,arg2);}
	uint8_t size()const{return sizeof(*this);}
	
	private:
	ClassType *Object;
	FuncType Slot;
	TypeArg0 arg0;
	TypeArg1 arg1;
	TypeArg2 arg2;
};



template <typename...Args>
AbstractTask * CreateTast(Args...args);

template <typename ClassType, typename...Args>
AbstractTask * CreateTast(ClassType *Object, void (ClassType::*Slot)(Args...), Args...args){
	return new ClassTask<ClassType,Args...>(Object,Slot,args...);
}

template <typename FuncType, typename...Args>
AbstractTask * CreateTast(FuncType F, Args...args){
	return new FunctionTask<FuncType,Args...>(F,args...);
}
#endif
