#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include "pipe.h"
#include <coroutine>
#include "scheduler.h"
#include "guard_trait.h"
#include <math.h>

#include "time_literals.h"

namespace asyncruino{

    template <
        Scheduler scheduler_t,Guard guard_t,
        typename time_t = size_t,typename size_type = size_t,size_type max_listeners = 64
    >
    struct timer_impl : sheduler_getter<scheduler_t>{
        guard_t m_guard;

        struct timer_info
        {
            timer_info():sch(0){}
			timer_info(time_t sch,std::coroutine_handle<> handle):
				sch(sch),handle(handle){}
            time_t sch;
            std::coroutine_handle<> handle;
        };
        timer_info m_list[max_listeners];

        timer_impl(scheduler_t & m_scheduler):sheduler_getter<scheduler_t>(m_scheduler){
        }


        inline void interrupt(){
            for(size_type i=0;i<max_listeners;++i){
                switch (m_list[i].sch)
                {
                case 0:
                    break;
                case 1:
                    m_list[i].sch--;
                    this->_get_sheduler().push_task(m_list[i].handle);
                    //m_guard.lock();
                    //m_guard.unlock();
                    break;
                default:
                    m_list[i].sch--;
                    break;
                }
            }
        }
        bool push_listener(std::coroutine_handle<> h,time_t m_delay){
            m_guard.lock();
            for(size_type i=0;i<max_listeners;++i){
                if(m_list[i].sch == 0){
                    m_list[i] = timer_info{m_delay,h};
                    
                    m_guard.unlock();
                    return true;
                }
            }
            m_guard.unlock();
            return false;
        }
        
        struct Delay_awaitor{
            time_t wait_ticks;
            timer_impl * m_timer;
            inline Delay_awaitor(time_t wait_ticks,timer_impl & _timer):
                wait_ticks(wait_ticks),m_timer(&_timer){}
            inline bool await_ready(){
                return wait_ticks == 0;
            }
            inline void await_resume(){}
            inline void await_suspend(std::coroutine_handle<> h){
                m_timer->push_listener(h,wait_ticks);
            }
        };
        inline Delay_awaitor Delay(time_t wait_ticks){
            wait_ticks = (wait_ticks ==0 ? 1 :wait_ticks);
            return Delay_awaitor(wait_ticks,*this);
        } 
    };
    
    template <typename timer_t>
    concept TimerConcept = requires (timer_t t){
        {t.Delay(0)};
        {t.interrupt()};
    };

    template <
        Scheduler scheduler_t,Guard guard_t,
        typename time_t = size_t,
        CounterImpl counter_t = timer_dim_counter<uint64_t,double,time_prefix::s>,
        typename size_type = size_t,size_t max_listeners = 64
    >
    struct timer_counter_impl: 
        public timer_impl<scheduler_t,guard_t,time_t,size_type,max_listeners>
    {
        typedef timer_impl<scheduler_t,guard_t,time_t,size_type,max_listeners> timer_base_t;
         
        typedef timer_dim_counter<
            typename counter_t::counter_type,
            typename counter_t::dividor_type,
            counter_t::base> m_counter_t;
        m_counter_t m_counter;

        /// @brief marker class for prefix (ns,mus,ms,s,...)
        //constexpr static counter_t::base base_i = {};

        template <int _pref = counter_t::base>
        timer_counter_impl(
            scheduler_t & m_scheduler,
            typename counter_t::dividor_type xsec_per_tick,
            time_prefix_t<_pref> _pr= {}):
            timer_base_t(m_scheduler),
            m_counter(xsec_per_tick,_pr){
        }
        void interrupt(){
            m_counter.value++;
            this->timer_base_t::interrupt();
        }
        void reset(){
            m_counter.value = 0;
        }
        template <int  _pref = counter_t::base>
        void set_speed(typename counter_t::dividor_type xsec_per_tick,
        time_prefix_t<_pref> _pr= {}){
            m_counter.set_speed(xsec_per_tick,_pr);
        }
        inline counter_t count()const {return m_counter.count();}

        template <int sec_prefix = counter_t::base>
        auto current(time_prefix_t<sec_prefix> _prfx = 
            time_prefix_t<sec_prefix>{})const{
            return m_counter.current(_prfx);
        } 
        
        template <typename _size_type,int sec_prefix>
        inline auto Delay(_size_type _delayed,time_prefix_t<sec_prefix> _prfx){
            return this->Delay(m_counter.to_counter_t(_delayed,_prfx));
        }; 

        template <typename _size_type>
        inline auto Delay(_size_type _delayed){
            return this->timer_base_t::Delay(_delayed);
        }

        inline auto tick_per()const{
            return m_counter.per_tick;
        }

    };

    template <typename T>
    concept TimerCounter = TimerConcept<T> && requires (T t){
        {t.Delay(0,time_prefix_t<time_prefix::s>{})};
        {t.current(time_prefix_t<time_prefix::s>{})};
        {t.count()};
        {t.reset()};
        {t.set_speed(0)};
    };
};

#endif//SIMPLE_TIMER_H