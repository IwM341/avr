#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "scheduler.hpp"
#include "default_guard.hpp"
/*
#ifndef
#define
#endif
*/

#ifndef TASK_QUEUE_SIZE
#define TASK_QUEUE_SIZE 200
#endif

#ifndef TASK_QUEUE_COMPRESS_ALIGN
#define TASK_QUEUE_COMPRESS_ALIGN false
#endif

#ifndef DELEGATE_LEAF_SIZE
#define DELEGATE_LEAF_SIZE 8
#endif

#ifndef POWER_MANAGER_CLASS_NAME
#define POWER_MANAGER_CLASS_NAME __rtu_no_power_manager__
#endif

struct POWER_MANAGER_CLASS_NAME;
typedef POWER_MANAGER_CLASS_NAME __rtu_global_power_manager_t; 

struct __rtu_no_power_manager__{
    inline static void sleep(){} 
};

#ifndef TASK_QUEUE_GUARD_TYPE
struct __rtu_global_no_guard_t : public rtu::no_guard_t{};
#define TASK_QUEUE_GUARD_TYPE __rtu_global_no_guard_t
#endif 

struct TASK_QUEUE_GUARD_TYPE;
typedef TASK_QUEUE_GUARD_TYPE __rtu_global_task_queue_guard_t; 


namespace rtu{
    
    typedef scheduler<TASK_QUEUE_SIZE,TASK_QUEUE_COMPRESS_ALIGN,
    __rtu_global_task_queue_guard_t,
    DELEGATE_LEAF_SIZE,__rtu_global_power_manager_t> scheduler_t;


    using scheduler_t::signal;
    using scheduler_t::terminate;

    struct Application{        
        Application(){
            __exec__enabled = true;
        }
        static void exec(){
            if(__exec__enabled){
                scheduler_t::exec();
            } 
        }
        private:
        static bool __exec__enabled;
    };
    bool Application::__exec__enabled = false;
};

#endif//APPLICATION_HPP