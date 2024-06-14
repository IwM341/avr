#ifndef TIMER_H
#define TIMER_H

#include "signals.h"
#include "micro_set.h"
namespace aos{

template <  typename size_type = size_t,
            uint8_t _soft_alarms = 4,
            uint8_t _soft_subscribers = 4,
            uint8_t _direct_alarms = 0,
            uint8_t _direct_subscribers = 0>
struct global_timer{
    constexpr static uint8_t soft_alarms = _soft_alarms;
    constexpr static uint8_t soft_subscribers = _soft_subscribers;
    constexpr static uint8_t direct_alarms = _direct_alarms;
    constexpr static uint8_t direct_subscribers = _direct_subscribers;
    

    typedef uint8_t S_ID;

    template <typename...FuncturConstructorArgs>
    S_ID subscribe_d(size_type delay, FuncturConstructorArgs&&...args){
        guard.lock();
        uint8_t res = _ds.insert(static_cast<FuncturConstructorArgs&&>(args)...);
        if(res != direct_subscribers){
            _dps[res] = delay-1;
            _drs[res] = delay-1;
        }
        guard.unlock();
        return res;
    }
    template <typename...FuncturConstructorArgs>
    S_ID subscribe_s(size_type delay,FuncturConstructorArgs&&...args){
        guard.lock();
        uint8_t res = _ss.insert(static_cast<FuncturConstructorArgs&&>(args)...);
        if(res != soft_subscribers){
            _sps[res] = delay-1;
            _srs[res] = delay-1;
        }
        guard.unlock();
        return res;
    }

    template <typename...FuncturConstructorArgs>
    void unsubscribe_d(FuncturConstructorArgs&&...args){
        guard.lock();
        _ds.remove(static_cast<FuncturConstructorArgs&&>(args)...);
        guard.unlock();
    }
    template <typename...FuncturConstructorArgs>
    void unsubscribe_s(FuncturConstructorArgs&&...args){
        guard.lock();
        _ss.remove(static_cast<FuncturConstructorArgs&&>(args)...);
        guard.unlock();
    }

    void unsubscribe_d(S_ID id){
        guard.lock();
        _ds.remove_it(id);
        guard.unlock();
    }
    void unsubscribe_s(S_ID id){
        guard.lock();
        _ss.remove_it(id);
        guard.unlock();
    }

    template <typename...FuncturConstructorArgs>
    S_ID alarm_d(size_type delay, FuncturConstructorArgs&&...args){
        guard.lock();
        uint8_t res = _da.insert(static_cast<FuncturConstructorArgs&&>(args)...);
        if(res != direct_alarms){
            _dra[res] = delay-1;
        }
        guard.unlock();
        return res;
    }
    template <typename...FuncturConstructorArgs>
    S_ID alarm_s(size_type delay, FuncturConstructorArgs&&...args){
        guard.lock();
        uint8_t res = _sa.insert(static_cast<FuncturConstructorArgs&&>(args)...);
        if(res != soft_alarms){
            _sra[res] = delay-1;
        }
        guard.unlock();
        return res;
    }

    template <typename...FuncturConstructorArgs>
    void unalarm_d(FuncturConstructorArgs&&...args){
        guard.lock();
        _dra.remove(static_cast<FuncturConstructorArgs&&>(args)...);
        guard.unlock();
    }
    void unalarm_d(S_ID id){
        guard.lock();
        _dra.remove_it(id);
        guard.unlock();
    }

    template <typename...FuncturConstructorArgs>
    void unalarm_s(FuncturConstructorArgs&&...args){
        guard.lock();
        _dra.remove(static_cast<FuncturConstructorArgs&&>(args)...);
        guard.unlock();
    }
    void unalarm_s(S_ID id){
        guard.lock();
        _sra.remove_it(id);
        guard.unlock();
    }

    void set_time(size_type new_time){
        instance().tick_num = new_time;
    }
    static size_type tiks(){
        return instance().tick_num;
    }
    static size_type time(){
        return instance().tick_num/instance().ticks_per_time;
    }
    static void set_ticks_per_time(size_type tpt){
        instance().ticks_per_tim=tpt;
    }

    void process_tick(){
        std::cout << "processing tick" << tick_num << std::endl;
        guard.lock();
        
        uint8_t i = 0;
        for(typename decltype(_da)::mask_type mask = 1; i != direct_alarms;++i,mask = mask << 1){
            if( (_da.contain(mask)) ){
                if(_dra[i] == 0){
                    _da.data()[i].call();
                    _da.remove_it(i);
                }else{
                    _dra[i] --;
                }
            }
            
        }
        i = 0;
        for(typename decltype(_ds)::mask_type mask = 1; i != direct_subscribers;++i,mask = mask << 1){
            if( (_ds.contain(mask)) ){
                if (_drs[i] == 0){
                    _ds.data()[i].call();
                    _drs[i] = _dps[i];
                }
                else{
                    _drs[i]--;
                }
            }
            
        }

        i = 0;
        auto & pipe = event_loop::get_pipe();
        pipe.lock();
        for(typename decltype(_sa)::mask_type mask = 1; i != soft_alarms;++i,mask = mask << 1){
            if( (_sa.contain(mask)) ){
                if(_sra[i] == 0){
                    __detail__::send_delegator(_sa.data()[i],pipe);
                    _sa.remove_it(i);
                }
                else{
                    _sra[i] --;
                }
            }
        }
        i = 0;
        for(typename decltype(_ds)::mask_type mask = 1; i != soft_subscribers;++i,mask = mask << 1){
            if( (_ss.contain(mask))){
                if(_srs[i] == 0){
                    __detail__::send_delegator(_ss.data()[i],pipe);
                    _srs[i] = _sps[i];
                }else{
                    _srs[i] --;
                }
            }
            
        }
        pipe.unlock();
        ++tick_num;
        guard.unlock();
    }

    static inline global_timer & instance(){
        static global_timer _gt;
        return _gt;
    }
    private:

    bool direct_lock;
    global_timer():tick_num(0),ticks_per_time(1),direct_lock(false){}
    size_type tick_num;
    size_type ticks_per_time;

    micro_set<ClassDelegator<>,direct_alarms> _da;
    size_type _dra[direct_alarms];
    micro_set<ClassDelegator<>,direct_subscribers> _ds;
    size_type _drs[direct_subscribers];
    size_type _dps[direct_subscribers];

    
    micro_set<ClassDelegator<>,soft_alarms> _sa;
    size_type _sra[soft_alarms];
    micro_set<ClassDelegator<>,soft_subscribers> _ss;
    size_type _srs[soft_subscribers];
    size_type _sps[soft_subscribers];
    __guard guard;
};

template <class TimerClass = global_timer<>>
auto & gtimer = TimerClass::instance();

};
#endif//TIMER_H