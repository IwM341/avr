/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <list>


class AbstractSenderInfo{
    public: 
    virtual void call( int ) = 0;
    virtual size_t size() const = 0;
    virtual ~AbstractSenderInfo(){}
    
    bool is_same (const AbstractSenderInfo * S){
        size_t N = this->size();
        if(N != S->size()){
            return false;
        }
        else{
            const char * bytes1 = reinterpret_cast<const char*> (this);
            const char * bytes2 = reinterpret_cast<const char*>(S);
            for(size_t i=0;i<N;++i){
                if(bytes1[i] != bytes2[i]){
                    return false;
                }
            }
            return true;
        }
    }
};
template <class Reciever>
struct ClassSlot : AbstractSenderInfo{
    typedef void (Reciever::*Function)(int);
    Reciever * Object;
    Function Func;
    
    ClassSlot(Reciever * Object,Function Func):Object(Object),Func(Func){}
    void call(int T){
        (Object->*Func)(T);
    }
    
    size_t size() const{
        return sizeof(ClassSlot);
    }
};
template <class Function>
struct FunctionSlot:AbstractSenderInfo{
    Function F;
    
    FunctionSlot(Function F):F(F){}
    
    void call(int T){
        F(T);
    }
    size_t size() const{
        return sizeof(FunctionSlot);
    }
};

class Sig{
    std::list<AbstractSenderInfo *> Funcs;
    public:
    
    template <class Reciever,class Function>
    void connect(Reciever * Object, Function F){
        AbstractSenderInfo * newASI = new ClassSlot<Reciever>(Object,F);
        for(auto it = Funcs.begin(); it!= Funcs.end();++it){
            if((*it)->is_same(newASI)){
                std::cout << "trying add exstig slot" <<std::endl;
                delete newASI;
                return;
            }
        }
        Funcs.push_back(newASI);
    }
    template <class Function>
    void connect(Function F){
        AbstractSenderInfo * newASI = new FunctionSlot<Function>(F);
        for(auto it = Funcs.begin(); it!= Funcs.end();++it){
            if((*it)->is_same(newASI)){
                std::cout << "trying add exstig slot" <<std::endl;
                delete newASI;
                return;
            }
        }
        Funcs.push_back(newASI);
    }
    template <class Reciever,class Function>
    void disconnect(Reciever * Object, Function F){
        AbstractSenderInfo * newASI = new ClassSlot<Reciever>(Object,F);
        for(auto it = Funcs.begin(); it!= Funcs.end();++it){
            if((*it)->is_same(newASI)){
                Funcs.remove(*it);
                delete (*it);
                delete newASI;
                return;
            }
        }
        std::cout << "didn't found connection" <<std::endl;
    }
    template <class Function>
    void disconnect(Function F){
        AbstractSenderInfo * newASI = new FunctionSlot<Function>(F);
        for(auto it = Funcs.begin(); it!= Funcs.end();++it){
            if((*it)->is_same(newASI)){
                Funcs.remove(*it);
                delete (*it);
                delete newASI;
                return;
            }
        }
        std::cout << "didn't found connection" <<std::endl;
    }
    
    void Signal(int T){
        std::cout << "begin { " <<std::endl;
        for(auto it = Funcs.begin(); it!= Funcs.end();++it){
            (*it)->call(T);
             std::cout << "size: " << (*it)->size() <<std::endl;
        }
        std::cout << "} end" <<std::endl;
    }
};

class A{
    public:
    void printA(int T){
        std::cout << "A prints " << T <<std::endl;
    }
};
class B{
    public:
    void printB(int T){
        std::cout << "B prints " << T <<std::endl;
    }
};

void Fun(int T){
    std::cout << "Function prints " << T <<std::endl;
}

int main()
{
    A a;
    B b;
    
    Sig S;
    S.connect(&a,&A::printA);
    S.connect(&b,&B::printB);
    S.connect(Fun);
    S.Signal(10);
    
    S.connect(&a,&A::printA);
    
    S.Signal(10);
    
    S.disconnect(&a,&A::printA);
    S.Signal(10);
    
    std::cout << "class size: " << sizeof(ClassSlot<A>) << ", func size:" << sizeof(FunctionSlot<void (*)(int)>) << std::endl;
    
    return 0;
}
