#ifndef DEFAULT_GUARD_HPP
#define DEFAULT_GUARD_HPP

namespace rtu{
    struct no_guard_t{
        inline void lock(){}
        inline void unlock(){}
    };

    template <typename __guard_t>
    struct lock_guard{
        __guard_t & __guard;
        inline lock_guard(__guard_t & __guard):__guard(__guard){
            __guard.lock();
        }
        inline ~lock_guard(){
            __guard.unlock();
        }
    };
};
#endif//DEFAULT_GUARD_HPP