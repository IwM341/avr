#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "pipe.h"
#include "guard_trait.h"
#include <coroutine>
#include <type_traits>
namespace asyncruino{
    template <Guard guard_type,size_t max_coro_num>
    struct scheduler_impl{
        pipe<std::coroutine_handle<>,size_t,max_coro_num> m_handles;
        guard_type m_pipe_guard;
        void (*sleep)(void);

        scheduler_impl():sleep(nullptr){}
        void run(){
            while(1){
                m_pipe_guard.lock();
                if(m_handles.empty()){
                    m_pipe_guard.unlock();
                    if(sleep){
                        sleep();
                    }
                } else {
                    std::coroutine_handle<> tmp_handle;
                    m_handles.read(tmp_handle);
                    m_pipe_guard.unlock();
                    tmp_handle.resume();
                }
            }
        }
        inline bool push_task(std::coroutine_handle<> new_handle){
            m_pipe_guard.lock();
            bool ret = m_handles.write(new_handle);
            m_pipe_guard.unlock();
            return ret;
        }
    };

    template <typename scheduler_t>
    concept Scheduler = requires (scheduler_t sch){
        {sch.push_task(std::coroutine_handle<> {})} -> std::same_as<bool>;
    };
    template <typename scheduler_t>
    concept StaticScheduler = Scheduler<scheduler_t> && requires (scheduler_t sch){
        {scheduler_t::instance()}->std::same_as<scheduler_t&>;
    };

    template <Scheduler sched_t>
    struct sheduler_getter{
        sched_t * m_shed;
        inline sched_t & _get_sheduler(){return *m_shed;}
        sheduler_getter(sched_t & _shed):m_shed(&_shed){}
    };

    template <StaticScheduler sched_t>
    struct sheduler_getter<sched_t>{
        inline static sched_t & _get_sheduler(){return sched_t::instance();}
        sheduler_getter(sched_t & _shed){}
        sheduler_getter(){}
    };

};
#endif//SCHEDULER_H