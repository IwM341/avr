#ifndef SIGNALS_HPP
#define SIGNALS_HPP


#define emit
#define slot

template <typename set_type>
struct force_signal{
    set_type slots;
    __guard__ g;

    template <typename...Args>
    void operator()(args...args){
        __guard__lock(&g);
        uint8_t size= slots.size();
        for(auto it = slots.begin();it!=slots.end();++it){
            it->call(args...);
        }
        __guard__unlock(&g);
    }

    bool connect(CreateArgs...cargs){
        __guard__lock(&g);
        return slots.insert(set_type::value_type(cargs...));
        __guard__unlock(&g);
    }
    template <typename...CreateArgs>
    bool disconnect(CreateArgs...cargs){
        __guard__lock(&g);
        return slots.remove(Delegator(cargs...));
        __guard__unlock(&g);
    }
};

template <typename set_type>
struct  soft_signal{
    set_type slots;
    Sheduler * sh;
    __guard__ g;
    template <typename...Args>
    void operator()(Args...args){
        __guard__lock(&g);
        for(auto it = slots.begin();it!=slots.end();++it){
            sh->call(*it,args...);
        }
        __guard__unlock(&g);
    }

    template <typename...CreateArgs>
    bool connect(CreateArgs...cargs){
        __guard__lock(&g);
        return slots.insert(Delegator(cargs...));
        __guard__unlock(&g);
    }
    template <typename...CreateArgs>
    bool disconnect(CreateArgs...cargs){
        __guard__lock(&g);
        return slots.remove(Delegator(cargs...));
        __guard__unlock(&g);
    }

};

template <typename SignalType,typename...SlotArgs>
bool connect(SignalType *signal,SlotArgs...args){
    return signal->connect(args...);
}
template <typename SignalType,typename...SlotArgs>
bool disconnect(SignalType *signal,SlotArgs...args){
    return signal->disconnect(args...);
}

#endif